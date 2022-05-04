/**
 * @file win32wlan.h
 * @author MatrixEditor
 * 
 * @brief This file contains basic definitions for using the native Wlan-API 
 * provided by Windows. If you want to use the code distributed by this 
 * repository add -lwlanapi and -lShlwapi as commandline parameters in order 
 * to include those libraries.
 * 
 * This API makes use of the Native Wifi API provided by Microsoft Windows:
 * "
 *    The Native Wifi API contains functions, structures, and enumerations 
 *    that support wireless network connectivity and wireless profile 
 *    management. The API can be used for both infrastructure and ad hoc 
 *    networks. The Wireless Ad Hoc API is a simplified object-oriented 
 *    interface for creating, managing, and using ad hoc networks.
 * "
 * 
 * The core functionalities are 'capturing' IEEE802.11 Beacon frames, list
 * all Wifi-Interfaces and parse InformationElements. Detailed information
 * about the structure of IE can be seen below.
 * 
 * Another advantage of this API is the export to the PCAP-Format. How the
 * export is performed will be described in win32pcap.h.
 * 
 * 
 * @version 0.1
 * @date 2022-05-03
 * 
 * @copyright Copyright (c) 2022
 */

#if !defined(_WIN32_NATIVE_WLAN_API_H_)
#define _WIN32_NATIVE_WLAN_API_H_

#include <Windows.h>
#include <wlanapi.h>
#include <Shlwapi.h>
#include <stdio.h>

#include "802dot11.h"

#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "Shlwapi.lib")

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/**
 * @brief A value that specifies whether the AP or peer station is operating 
 * within the regulatory domain as identified by the country/region. 
 * 
 * If the wireless LAN interface driver does not support multiple regulatory 
 * domains, this member is set to TRUE. 
 * 
 * If the 802.11 Beacon or Probe Response frame received from the AP or peer 
 * station does not include a Country information element (IE), this member 
 * is set to TRUE. 
 * 
 * If the 802.11 Beacon or Probe Response frame received from the AP or peer 
 * station does include a Country IE, this member is set to FALSE if the value
 * of the Country String subfield does not equal the input country string.
 */
#define IsInRegularotyDomain(x) (x == TRUE)

/**
 * @brief A scan for networks has completed.
 */
#define WLANAPI_NOTE_ACM_SCAN_COMLETE 0x00000007

/**
 * @brief A scan for connectable networks failed. The pData member points to 
 * a WLAN_REASON_CODE data type value that identifies the reason the WLAN 
 * operation failed.
 */
#define WLANAPI_NOTE_ACM_SCAN_FAIL 0x00000008

/**
 * @brief A connection has started to a network in range. The pData member points 
 * to a WLAN_CONNECTION_NOTIFICATION_DATA structure that identifies the network 
 * information for the connection attempt.
 */
#define WLANAPI_NOTE_ACM_SCAN_START 0x00000009

/**
 * @brief This value is supported on Windows 8 and later.
 */
#define WLANAPI_NOTE_ACM_SCAN_LIST_REFRESH 0x0000001a

/**
 * @brief Used to indicate whether the field or methods requires admin 
 * priviledges.
 */
#define __asadmin

/**
 * @brief A small const wrapper.
 */
#define __const const

/**
 * @brief A small descriptor for parameters or return values that have to be 
 * or that will be in a specific range.
 */
#define _Range(min, max)

/**
 * @brief Frees memory of native wifi objects. Any memory returned from Native 
 * Wifi functions must be freed.
 */
#define wlanapi_free(pObj) WlanFreeMemory((VOID *)pObj)

/**
 * @brief The value of the Capability Information field from the 802.11 Beacon or 
 * Probe Response frame received by the wireless LAN interface. This value is a set of bit flags defining the capability.
 */
typedef enum _WLANAPI_CAPABLITY_INFO {
  /**
   * @brief An extended service set. A set of one or more interconnected basic 
   * service sets (BSSs) and integrated local area networks (LANs) that appears
   * as a single BSS to the logical link control layer at any station associated 
   * with one of those BSSs. 
   * 
   * An AP set the ESS subfield to 1 and the IBSS subfield to 0 within transmitted 
   * Beacon or Probe Response frames. A peer station within an IBSS (ad hoc network) 
   * sets the ESS subfield to 0 and the IBSS subfield to 1 in transmitted Beacon or 
   * Probe Response frames.
   * 
   * \bit: 0
   */
  ESS   = 0x1,

  /**
   * @brief An independent basic service set. A BSS that forms a self-contained network,
   * and in which no access to a distribution system (DS) is available (an ad hoc 
   * network). 
   * 
   * \bit: 1
   */
  IBSS  = 0x2,

  /**
   * @brief A value that indicates if the AP or peer station is pollable.
   * 
   * \bit: 2
   */
  CF_POLLABLE = 0x4,

  /**
   * @brief A value that indicates how the AP or peer station handles poll requests.
   * 
   * \bit: 3
   */
  CF_POLL_REQUEST = 0x8,

  /**
   * @brief A value that indicates if encryption is required for all data frames. An AP 
   * sets the Privacy subfield to 1 within transmitted Beacon and Probe Response frames
   * if WEP, WPA, or WPA2 encryption is required for all data type frames exchanged within the BSS.
   * 
   * If WEP, WPA, or WPA2 encryption is not required, the Privacy subfield is set to 0.
   * 
   * \bit: 4
   */
  PRIVACY = 0x10

} WLANAPI_CAPABLITY_INFO, *PWLANAPI_CAPABLITY_INFO;

/**
 * @brief The DOT11_BSS_TYPE enumerated type defines a basic service set 
 * (BSS) network type.
 * 
 * \see wlantypes.h
 */
typedef enum _WLANAPI_DOT11_BSS_TYPE {
  /**
   * @brief Specifies an infrastructure BSS network.
   */
  infrastructure = 1,

  /**
   * @brief Specifies an independent BSS (IBSS) network (an ad hoc 
   * network). 
   */
  independent,

  /**
   * @brief Specifies either infrastructure or IBSS network.
   */
  bss_any
} WLANAPI_DOT11_BSS_TYPE, *PWLANAPI_DOT11_BSS_TYPE;

/**
 * @brief The DOT11_PHY_TYPE enumeration defines an 802.11 PHY and media type.
 *
 * \see wlantypes.h
 */
typedef enum _WLANAPI_DOT11_PHY_TYPE {
  /**
   * @brief Specifies an unknown or uninitialized PHY type.
   */
  unknown     = 0,

  /**
   * @brief Specifies any PHY type.
   */
  phy_any         = 0,

  /**
   * @brief Specifies a frequency-hopping spread-spectrum (FHSS) PHY. Bluetooth 
   * devices can use FHSS or an adaptation of FHSS.
   */
  fhss,

  /**
   * @brief Specifies a direct sequence spread spectrum (DSSS) PHY type.
   */
  dsss,

  /**
   * @brief Specifies an infrared (IR) baseband PHY type.
   */
  irbaseband,
  
  /**
   * @brief Specifies an orthogonal frequency division multiplexing (OFDM) PHY 
   * type. 802.11a devices can use OFDM.
   * 
   */
  ofm,

  /**
   * @brief Specifies a high-rate DSSS (HRDSSS) PHY type.
   */
  hrdsss,

  /**
   * @brief Specifies an extended rate PHY type (ERP). 802.11g devices can 
   * use ERP.
   */
  erp,
  
  /**
   * @brief Specifies the 802.11n PHY type.
   */
  ht,

  /**
   * @brief Specifies the 802.11ac PHY type. This is the very high throughput PHY 
   * type specified in IEEE 802.11ac.This value is supported on Windows 8.1, Windows
   * Server 2012 R2, and later.
   */
  vht,

  /**
   * @brief Specifies the start of the range that is used to define PHY types that are 
   * developed by an independent hardware vendor (IHV).
   */
  IHV_start   = 0x80000000,

  /**
   * @brief Specifies the start of the range that is used to define PHY types that are 
   * developed by an independent hardware vendor (IHV).
   */
  IHV_end     = 0xffffffff
} WLANAPI_DOT11_PHY_TYPE, *PWLANAPI_DOT11_PHY_TYPE;

/**
 * @brief Information elements are defined in the IEEE 802.11 specifications to have a 
 * common general format consisting of a 1-byte Element ID field, a 1-byte Length field, 
 * and a variable-length element-specific information field. 
 * 
 * Each information element is assigned a unique Element ID value as defined in this IEEE 
 * 802.11 standards. The Length field specifies the number of bytes in the information 
 * field.
 * 
 * @note The information element is linked with a BYTE pointer which stores the actual 
 * information of this element. To save memory the needed space is allocated when the 
 * element is generated.
 */
typedef struct _WLANAPI_IE_BLOB {
  /**
   * @brief The identifier to determine the type of this blob.
   * 
   * @type: [unsigned char] (8 bits)
   */
  BYTE ieId;

  /**
   * @brief The size, in bytes, of the IE data blob. The maximum value for the size of 
   * the IE data blob is 2,324 bytes.
   * 
   * @type: unsigned char (8 bits)
   */
  BYTE ieSize;

  /**
   * @brief A buffer that contains variable-length information elements (IEs) from the 
   * 802.11 Beacon or Probe Response frames.
   * 
   * If an IE is available in only one frame, the wireless LAN interface driver merges 
   * the IE with the other IEs from the last received Beacon or Probe Response frame.
   * 
   * @type: unsigned char * (8 bits)
   */
  BYTE *pIelement;
} WLANAPI_IE_BLOB, *PWLANAPI_IE_BLOB;

/**
 * @brief The WLANAPI_802DOT11_FRAME structure contains information about the collected
 * information from the wifi network scan.
 */
typedef struct _WLANAPI_802DOT11_FRAME {
  /**
   * @brief The SSID that is specified by the bSSID 
   * member is not a null-terminated ASCII string. The 
   * length of the SSID is determined by the ulSSIDLength 
   * member.
   * 
   * A wildcard SSID is an SSID whose uSSIDLength member 
   * is set to zero. When the desired SSID is set to the 
   * wildcard SSID, the 802.11 station can connect to any 
   * basic service set (BSS) network.
   * 
   * @type: unsigned char[32] (8 bits)
   */
  BYTE bSSID[32];

  /**
   * @brief The length, in bytes, of the ucSSID array.
   * 
   * @type: unsigned long (32 bits)
   */
  ULONG ulSSIDLength;

  /**
   * @brief The identifier (ID) of the PHY that the wireless 
   * LAN interface used to detect the BSS network.
   * 
   * @type: unsigned long (32 bits)
   */
  ULONG phyId;
  
  /**
   * @brief The PHY type for this network.
   */
  WLANAPI_DOT11_PHY_TYPE phyType;

  /**
   * @brief The IEEE media access control (MAC) address in unicast,
   * multicast, or broadcast format.
   * 
   * @type: unsigned char[6] (8 bits)
   */
  BYTE macAddress[6];

  /**
   * @brief The BSS network type.
   */
  WLANAPI_DOT11_BSS_TYPE bssType;

  /**
   * @brief A value that specifies whether the AP or peer station is 
   * operating within the regulatory domain as identified by the
   * country/region.
   * 
   * @type: unsigned char (8 bits)
   */
  BOOLEAN inRegDomain;

  /**
   * @brief The value of the Capability Information field from the 
   * 802.11 Beacon or Probe Response frame received by the wireless 
   * LAN interface. This value is a set of bit flags defining the 
   * capability.
   */
  USHORT capabilities;

  /**
   * @brief The value of the Timestamp field from the 802.11 Beacon
   * or Probe Response frame received by the wireless LAN interface.
   * 
   * @type: unsigned long long (64 bits)
   */
  ULONGLONG timestamp;

  /**
   * @brief A pointer to the information element (IE) data blob.
   */
  PWLANAPI_IE_BLOB ieBlob;

} WLANAPI_802DOT11_FRAME, *PWLANAPI_802DOT11_FRAME;

typedef struct _WLANAPI_BEACON_HEADER {
  /**
   * @brief The frame control field specifies some informative flags 
   * used in beacon frames. Unfortunately, this field cannot be 
   * reproduced through the data from native function calls.
   * 
   * @type: [unsigned short] (16 bits)
   */
  USHORT usFrameControl;

  /**
   * @brief Microseconds of the frame duration (also 0).
   * 
   * @type: [unsigned short] (16 bits)
   */
  USHORT usDuration;

  /**
   * @brief The destination address is set to the ethernet Broadcast
   * (ff:ff:ff:ff:ff:ff) within 6 bytes.
   * 
   * @type: [unsigned char *] (6 bytes total length)
   */
  BYTE ucDestination[6];

  /**
   * @brief The IEEE media access control (MAC) address in unicast,
   * multicast, or broadcast format. (equal to the ucBSSID field)
   * 
   * @type: [unsigned char *] (6 bytes total length)
   */
  BYTE ucSource[6];

  /**
   * @see WLANAPI_BEACON_HEADER::usSource
   */
  BYTE ucBSSID[6];

  /**
   * @brief The sequence number of this beacon frame. Unfortuntealy, this 
   * property cannot be queried. 
   * 
   * @type: [unsigned short] (16 bits)
   */
  USHORT usSeq;
} WLANAPI_BEACON_HEADER, *PWLANAPI_BEACON_HEADER;

/**
 * @brief Beacon frames are used by the access points (and stations in an IBSS) 
 * to communicate throughout the serviced area the characteristics of the connection
 * offered to the cell members. This information used by clients trying to connect 
 * to the network as well as clients already associated to the BSS. 
 * 
 * Beacons are sent periodically at a time called Target Beacon Transmission Time 
 * (TBTT): 
 *      1 TU = 1024 microseconds 
 *      Beacon interval = 100 TU (100x 1024 microseconds or 102.4 milliseconds)
 */
typedef struct _WLANAPI_BEACON_FRAME {
  /**
   * @brief the mac header contains information about the sender of this beacon 
   * frame.
   */
  WLANAPI_BEACON_HEADER header;

  /**
   * @brief A value representing the time on the access point, which is the number 
   * of microseconds the AP has been active. When timestamp reach its max 
   * (2^64 microsecond or ~580,000 years) it will reset to 0.
   * 
   * @type: [unsinged long long] (64 bits)
   */
  ULONGLONG ullTimestamp;

  /**
   * @brief Beacon Interval field represent the number of time units (TU) 
   * between target beacon transmission times (TBTT). Default value is 100TU 
   * (102.4 milliseconds).
   * 
   * @type: [unsigned short] (16 bits)
   */
  USHORT usInterval;

  /**
   * @brief This field contains number of subfields that are used to indicate 
   * requested or advertised optional capabilities.
   * 
   * @type: [unsigned short] (16 bits)
   */
  USHORT usCapabilities;

  /**
   * @brief Present in all Beacons, probe requests, probe responses,association 
   * request & re-association requests. Element ID is 0 for the SSID IE. SSID 
   * could have a maximum of 32 characters.
   */
  WLANAPI_IE_BLOB ieSSID;

  /**
   * @brief This is present in Beacons, Probe Req, Probe Res, Association Req, 
   * Association Res, Reassociation Req and  Reassociation Response. It is an 8 
   * octet field where each octet describe a single supported rate. 
   * 
   * Last bit (7th) of each octet indicates whether the data rate is “basic rate 
   * or mandatory” or “supported rate”. 
   */
  WLANAPI_IE_BLOB ieSupportedRates;
  
  /**
   * @brief The frame checksum (not available).
   * 
   * @type: [unsigned short] (16 bits)
   */
  USHORT uiFrameCS;

  /**
   * @brief Defines the length of the data pIeDataBlob points to.
   * 
   * @type: unsigned long (32 bits)
   */
  DWORD ulIeLength;

  /**
   * @brief A storage pointer which points drectly to native data. It is 
   * recommended to copy this data before working with it. This data is deleted
   * if wlanapi_free is called.
   */
  BYTE *pIeDataBlob;

} WLANAPI_BEACON_FRAME, *PWLANAPI_BEACON_FRAME;

/**
 * @brief Creates but does not allocate a new WLANAPI_802DOT11_FRAME structure
 * with the given bssEntry.
 * 
 * @param _Entry The WLAN_BSS_ENTRY structure contains information about a 
 *               basic service set (BSS).
 * @param _Frame A pointer to the frame that will be filled. This pointer 
 *               must point to a real address with an allocated object. 
 * @return [unsigned long] If the function succeeds, the return value is 
 *         ERROR_SUCCESS. 
 *         If the function fails, the return value may be one of the following 
 *         return codes:
 *            - ERROR_INVALID_PARAMETER = 87,
 *            - ERROR_NOT_ENOUGH_MEMORY = 8
 * @name Dot11Frame
 */
DWORD __cdecl __etop_802_frame(__const PWLAN_BSS_ENTRY _Entry, PWLANAPI_802DOT11_FRAME _Frame);
#define Dot11Frame(_Entry, _pFrame) \
  __etop_802_frame((__const PWLAN_BSS_ENTRY)_Entry, (PWLANAPI_802DOT11_FRAME)_Frame)

/**
 * @brief Creates but does not allocate a new WLANAPI_BEACON_FRAME structure
 * with the given bssEntry.
 * 
 * @param _Entry The WLAN_BSS_ENTRY structure contains information about a 
 *               basic service set (BSS).
 * @param _Frame A pointer to the frame that will be filled. This pointer 
 *               must point to a real address with an allocated object. 
 * @return [unsigned long] If the function succeeds, the return value is 
 *         ERROR_SUCCESS. 
 *         If the function fails, the return value may be one of the following 
 *         return codes:
 *            - ERROR_INVALID_PARAMETER = 87,
 *            - ERROR_NOT_ENOUGH_MEMORY = 8
 * @name Get802Dot11Beacon
 */
DWORD __cdecl __etop_ieee802_beacon(__const PWLAN_BSS_ENTRY _Entry, PWLANAPI_BEACON_FRAME _Frame);
#define Get802Dot11Beacon(_pEntry, _pFrame) \
  __etop_ieee802_beacon((__const PWLAN_BSS_ENTRY) _pEntry, (PWLANAPI_BEACON_FRAME) _pFrame)

/**
 * @brief Enumerates all of the wireless LAN interfaces currently enabled on 
 * the local computer and returnes the interface of the given index.
 * 
 * @param _Client The client's session handle, obtained by a previous call 
 *                to the WlanOpenHandle function.
 * @param _Index The interface index
 * @param _IfaceInfo A pointer to storage for a pointer to receive the returned 
 *                  wireless LAN interface info.
 * @return [unsigned long] If the function succeeds, the return value is 
 *         ERROR_SUCCESS. 
 *         If the function fails, the return value may be one of the following 
 *         return codes:
 *            - ERROR_INVALID_PARAMETER = 87,
 *            - ERROR_INVALID_HANDLE    = 6,
 *            - ERROR_NOT_ENOUGH_MEMORY = 8,
 *            - ERROR_NOT_FOUND         = 1168
 * @name GetInterfaceInfo
 */
DWORD __cdecl __atop_iface_info(HANDLE _Client, _Range(0, ULONG_MAX) __const ULONG _Index, PWLAN_INTERFACE_INFO _IfaceInfo);
#define GetInterfaceInfo(_Client, _Index, _pIfaceInfo) \
  __atop_iface_info((HANDLE)_Client, (__const ULONG)_Index, (PWLAN_INTERFACE_INFO)_pIfaceInfo)

#ifdef WLAN_DEVICE_SERVICE_GUID_LIST
/**
 * @brief Retrieves a list of the supported device services on a given wireless
 * LAN interface.
 * 
 * \note 
 * If the function succeeds, the return value is ERROR_SUCCESS. If the function 
 * fails with ERROR_ACCESS_DENIED, then the caller doesn't have sufficient 
 * permissions to perform this operation. The caller needs to either have admin 
 * privilege, or needs to be a UMDF driver.
 * 
 * @param _Client The client's session handle, obtained by a previous call to 
 *                the WlanOpenHandle function.
 * @param _IfaceGuid A pointer to the GUID of the wireless LAN interface to be 
 *                   queried.
 * @param _SrvList A pointer to storage for a pointer to receive the returned 
 *                 list of device service GUIDs.
 * @return [unsigned long] If the function succeeds, the return value is 
 *         ERROR_SUCCESS else the function fails with ERROR_ACCESS_DENIED.
 * @name GetInterfaceServices
 */
DWORD __cdecl __asadmin __atop_iface_srvs(HANDLE _Client, __const GUID *_IfaceGuid, WLAN_DEVICE_SERVICE_GUID_LIST *_SrvList);
#define GetInterfaceServices(_Client, _IfaceGuid, _SrvList) \
  __atop_iface_srvs((HANDLE)_Client, (__const GUID *)_IfaceGuid, (PWLAN_DEVICE_SERVICE_GUID_LIST *)_SrvList)

#endif

/**
 * @brief The register_cb function is used to register notifications on all 
 * wireless interfaces.
 * 
 * @param _Client The client's session handle, obtained by a previous call to the 
 *                WlanOpenHandle function.
 * @param _Callback A WLAN_NOTIFICATION_CALLBACK type that defines the type of
 *                  notification callback function.
 * @param _Context A pointer to the client context that will be passed to the 
 *                 callback function with the notification.
 * @return [unsigned long] 0 for success else any windows error
 * @name RegisterCallback
 */
DWORD __cdecl __atof_register_cb(HANDLE _Client, WLAN_NOTIFICATION_CALLBACK _Callback, PVOID _Context);
#define RegisterCallback(_Client, _Callback, _Context) \
  __atof_register_cb((HANDLE)_Client, (WLAN_NOTIFICATION_CALLBACK)_Callback, (PVOID)_Context)

/**
 * @brief Opens a connection to the server.
 * 
 * @param _Client A handle for the client to use in this session. This handle 
 *                is used by other functions throughout the session.
 * @return [unsigned long] If the function succeeds, the return value is 
 *         ERROR_SUCCESS, otherwise:
 *          - ERROR_INVALID_PARAMETER             = 87,
 *          - ERROR_NOT_ENOUGH_MEMORY             = 8,
 *          - ERROR_REMOTE_SESSION_LIMIT_EXCEEDED = 1220
 * @name GetSession
 */
DWORD __cdecl __ftop_get_handle(HANDLE *_Client);
#define GetSession(_Client) __ftop_get_handle((HANDLE *)_Client)

/**
 * @brief Returns a qualified null-terminated string that contains the interface
 * description of the given adapter. 
 * 
 * @param _IfaceInfo the interface info
 * @return const char* the interface description 
 * @name GetIfaceDescription
 */
__const CHAR *__cdecl __atop_iface_desc(PWLAN_INTERFACE_INFO _IfaceInfo);
#define GetIfaceDescription(_IfaceInfo) __atop_iface_desc((PWLAN_INTERFACE_INFO) _IfaceInfo)

/**
 * @brief Constructs a information element structure with the given byte blob. Note, 
 * that the element pointer will be NULL if the ieId is not defined in the win32ieee802.h
 * header file.
 * 
 * @param pIeDataBlob the data blob
 * @param _Offset the current offset
 * @return __const InformationElement
 */
__const PWLANAPI_IE_BLOB __atop_get_ieblob(__const BYTE *pIeDataBlob, __const DWORD _Offset);
#define ConvertBlobToIE(pIeDataBlob, _Offset) \
  __atop_get_ieblob((__const BYTE *)pIeDataBlob, (__const DWORD) _Offset)

/**
 * @brief A convenient macro to start 'capturing' packets. The WlanScan function requests 
 * a scan for available networks on the indicated interface. 
 * 
 * Before calling the WlanScan function there should be a callback registered in the system 
 * in order to handle notifications.
 */
#define StartCapture(_Client, _pGuid) \
  if (WlanScan((HANDLE)_Client, (__const GUID *)_pGuid, NULL, NULL, NULL) == ERROR_SUCCESS) { \
    while (1) { Sleep(4000); } \
  }

/**
 * @brief A simple macro to get the NetworkBssList from the native wireless api with less
 * parameters.
 */
#define NETBssList(_Client, _pGuid, _pList) \
  WlanGetNetworkBssList((HANDLE)hClient, (__const GUID *)_pGuid, NULL, (DOT11_BSS_TYPE)1, FALSE, NULL, _pList)

#define DefCallBackFn(name) VOID name(PWLAN_NOTIFICATION_DATA _Data, PVOID _Context)
#define ImplCallBackFn(name, code) VOID name(PWLAN_NOTIFICATION_DATA _Data, PVOID _Context) { \
  if (_Data->NotificationCode == WLANAPI_NOTE_ACM_SCAN_COMLETE) code \
}

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // _WIN32_NATIVE_WLAN_API_H_
