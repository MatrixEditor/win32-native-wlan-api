#include "../win32/native/include/win32wlan.h"
#include "../win32/native/include/802dot11fmt.h"

ImplCallBackFn(handleNotification, {
  HANDLE hClient = (HANDLE)_Context;
  PWLAN_BSS_LIST list = NULL;


  DWORD result = NETBssList(hClient, &_Data->InterfaceGuid, &list);
  for (DWORD i = 0; i < list->dwNumberOfItems; i++) {
    PWLAN_BSS_ENTRY pEntry = &list->wlanBssEntries[i];
    WLANAPI_BEACON_FRAME beacon;
    result = Get802Dot11Beacon(pEntry, &beacon);

    Print802(&beacon, FMT_OPTION_COLOUR);
    exit(0);
  }
})

VOID handleNotification(PWLAN_NOTIFICATION_DATA pData, PVOID pV) {
  switch (pData->NotificationCode) {
    case WLANAPI_NOTE_ACM_SCAN_COMLETE: {
      HANDLE hClient = (HANDLE)pV;
      PWLAN_BSS_LIST list = NULL;


      DWORD result = NETBssList(hClient, &pData->InterfaceGuid, &list);
      for (DWORD i = 0; i < list->dwNumberOfItems; i++)
      {
        PWLAN_BSS_ENTRY pEntry = &list->wlanBssEntries[i];
        WLANAPI_BEACON_FRAME beacon;
        result = Get802Dot11Beacon(pEntry, &beacon);

        Print802(&beacon, FMT_OPTION_COLOUR);
        exit(0);
      }
      
    }
  }
}

int main(int argc, char const *argv[])
{
  HANDLE hClient;
  if (GetSession(&hClient) > 0) {
    return -1;
  }

  WLAN_INTERFACE_INFO info;
  if (GetInterfaceInfo(hClient, 0, &info) > 0) {
    return -1;
  }

  if (RegisterCallback(hClient, &handleNotification, hClient) > 0) {
    return -1;
  } 

  StartCapture(hClient, &info.InterfaceGuid);

  return 0;
}
