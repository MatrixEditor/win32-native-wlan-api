#include "../include/win32wlan.h"

DWORD __atof_register_cb(HANDLE _Client, WLAN_NOTIFICATION_CALLBACK _Callback, PVOID _Context) 
{
  DWORD result = ERROR_SUCCESS;

  if (!_Client || !_Callback) {
    result = ERROR_INVALID_PARAMETER;
    goto cleanup;
  }

  result = WlanRegisterNotification(_Client, 0x0000FFFF, TRUE, _Callback, _Context, NULL, NULL);
  goto cleanup;

  cleanup: {
    return result;
  }
}

#ifdef WLAN_DEVICE_SERVICE_GUID_LIST

DWORD __asadmin __atop_iface_srvs(HANDLE _Client, __const GUID *_IfaceGuid, WLAN_DEVICE_SERVICE_GUID_LIST *_SrvList) 
{
  DWORD result = ERROR_SUCCESS;

  if (!_Client || !_IfaceGuid) {
    result = ERROR_INVALID_PARAMETER;
    _SrvList = NULL;
    goto cleanup;
  }

  result = WlanGetSupportedDeviceServices(_Client, _IfaceGuid, &_SrvList);
  goto cleanup;

  cleanup: {
    if (result != ERROR_SUCCESS && _SrvList) {
      wlanapi_free(_SrvList);
    }
    return result;
  }
}

#endif

DWORD __atop_iface_info(HANDLE _Client, __const ULONG _Index, PWLAN_INTERFACE_INFO _IfaceInfo)
{
  DWORD result = ERROR_SUCCESS;
  PWLAN_INTERFACE_INFO_LIST ifaceInfoList = NULL;

  if (!_Client || _Index < 0) {
    result = ERROR_INVALID_PARAMETER;
    goto cleanup;
  }

  result = WlanEnumInterfaces(_Client, NULL, &ifaceInfoList);
  if (result != ERROR_SUCCESS) {
    goto cleanup;
  }

  if (ifaceInfoList->dwNumberOfItems <= _Index) {
    result = ERROR_INVALID_PARAMETER;
    goto cleanup;
  }

  if (!_IfaceInfo) {
    _IfaceInfo = (PWLAN_INTERFACE_INFO)malloc(sizeof(WLAN_INTERFACE_INFO));
  }
  memcpy((VOID *)_IfaceInfo, (__const VOID *)&ifaceInfoList->InterfaceInfo[_Index], sizeof(WLAN_INTERFACE_INFO));
  goto cleanup;

  cleanup: {
    if (ifaceInfoList) {
      wlanapi_free(ifaceInfoList);
    }
    return result;
  }
}

DWORD __etop_802_frame(__const PWLAN_BSS_ENTRY _Entry, PWLANAPI_802DOT11_FRAME _Frame)
{
  if (!_Entry || !_Frame) {
    return ERROR_INVALID_PARAMETER;
  }

  _Frame->ulSSIDLength = _Entry->dot11Ssid.uSSIDLength;
  _Frame->phyId = _Entry->uPhyId;
  _Frame->phyType = (WLANAPI_DOT11_PHY_TYPE)_Entry->dot11BssPhyType;
  _Frame->bssType = (WLANAPI_DOT11_BSS_TYPE)_Entry->dot11BssType;
  _Frame->inRegDomain = IsInRegularotyDomain(_Entry->bInRegDomain);
  _Frame->capabilities = _Entry->usCapabilityInformation;
  _Frame->timestamp = _Entry->ullTimestamp;

  memcpy((VOID *) _Frame->bSSID, (__const VOID *)_Entry->dot11Ssid.ucSSID, _Frame->ulSSIDLength);
  memcpy((VOID *) _Frame->macAddress, (__const VOID *)_Entry->dot11Bssid, 6);

  if (_Entry->ulIeSize == 0) {
    return ERROR_SUCCESS;
  }

  PWLANAPI_IE_BLOB ieBlob = _Frame->ieBlob;
  PBYTE pIelementBlob = (PBYTE)_Entry + _Entry->ulIeOffset;

  ieBlob->ieSize = _Entry->ulIeSize;
  memcpy((VOID *) ieBlob->pIelement, (__const VOID *)pIelementBlob, ieBlob->ieSize);
  return ERROR_SUCCESS;
}

DWORD __ftop_get_handle(HANDLE *_Client) 
{
  DWORD clientVersion = 2;
  DWORD version = 0;
  
  return WlanOpenHandle(clientVersion, NULL, &version, _Client);
}

__const CHAR *__atop_iface_desc(PWLAN_INTERFACE_INFO _IfaceInfo)
{
  if (!_IfaceInfo) {
    return ("");
  }

  CHAR *desc = malloc(256);
  if (!desc) {
    return ("");
  } 

  DWORD i = 0;
  WCHAR c = 0;
  while (c = _IfaceInfo->strInterfaceDescription[i]) {
    desc[i++] = c;
  }

  desc[i] = 0x00;
  return desc;
}

DWORD __etop_ieee802_beacon(__const PWLAN_BSS_ENTRY _Entry, PWLANAPI_BEACON_FRAME _Frame)
{
  if (!_Frame || !_Entry) {
    return ERROR_INVALID_PARAMETER;
  }
  // header
  _Frame->header.usFrameControl = 0x00, _Frame->header.usDuration = 0x00;
  _Frame->header.usSeq = 0x00;
  memset((VOID *)_Frame->header.ucDestination, 0xff, 6);
  memcpy((VOID *)_Frame->header.ucSource, (__const VOID *)_Entry->dot11Bssid, 6);
  memcpy((VOID *)_Frame->header.ucBSSID, (__const VOID *)_Entry->dot11Bssid, 6);

  // body
  _Frame->uiFrameCS = IEEE80211_TYPE_MGMT, _Frame->ullTimestamp = _Entry->ullTimestamp;
  _Frame->usInterval = _Entry->usBeaconPeriod;
  _Frame->usCapabilities = _Entry->usCapabilityInformation;

  PWLANAPI_IE_BLOB ssid = &_Frame->ieSSID;
  ssid->ieId = IE_SSID;
  ssid->ieSize = (BYTE)_Entry->dot11Ssid.uSSIDLength;
  if (ssid->ieSize > 0) {
    ssid->pIelement = (BYTE *)malloc(ssid->ieSize);
    memcpy((VOID *)ssid->pIelement, (__const VOID *) _Entry->dot11Ssid.ucSSID, ssid->ieSize);
  } else {
    ssid->pIelement = NULL;
  }
  
  PWLANAPI_IE_BLOB rates = &_Frame->ieSupportedRates;
  rates->ieId = IE_SUPPORTED_RATES;
  rates->ieSize = (BYTE)_Entry->wlanRateSet.uRateSetLength;
  rates->pIelement = (BYTE *)malloc(ssid->ieSize);
  memcpy((VOID *)rates->pIelement, (__const VOID *) _Entry->wlanRateSet.usRateSet, rates->ieSize);

  _Frame->pIeDataBlob = (PBYTE)_Entry + _Entry->ulIeOffset;
  _Frame->ulIeLength = _Entry->ulIeSize;
  return ERROR_SUCCESS;
}

__const PWLANAPI_IE_BLOB __atop_get_ieblob(__const BYTE *pIeDataBlob, __const DWORD _Offset) 
{
  if (!pIeDataBlob) {
    return (PWLANAPI_IE_BLOB)0;
  }

  BYTE id = pIeDataBlob[_Offset];
  BYTE size = pIeDataBlob[_Offset + 1];
  PWLANAPI_IE_BLOB ie = (PWLANAPI_IE_BLOB)malloc(sizeof(WLANAPI_IE_BLOB));
  
  ie->ieId = id;
  ie->ieSize = size;
  if (IsReserverd_IE(id)) {
    ie->pIelement = NULL;
    return  ie;
  }

  ie->pIelement = (BYTE *)malloc(size);
  memcpy((VOID *)ie->pIelement, (__const VOID *)(pIeDataBlob + _Offset + 2), size);
  return ie;
}