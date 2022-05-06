#include "../win32/native/include/win32wlan.h"
#include "../win32/native/include/802dot11fmt.h"

#define PROG_BANNER "\
============================================================================\n\
                      WLAN-Capturing v1\n\
============================================================================\n\
Usage:\
\tcapture.exe [--no-color] [-1] [--table]\n\n"

static BOOLEAN stop = FALSE;

VOID handleNotification(PWLAN_NOTIFICATION_DATA _Data, PVOID _Context) { 
  if (_Data->NotificationCode == WLANAPI_NOTE_ACM_SCAN_COMLETE) {
    HANDLE hClient = (HANDLE)_Context;
    PWLAN_BSS_LIST list = NULL;


    DWORD result = NETBssList(hClient, &_Data->InterfaceGuid, &list);
    for (DWORD i = 0; i < list->dwNumberOfItems && !stop; i++) {
      PWLAN_BSS_ENTRY pEntry = &list->wlanBssEntries[i];
      WLANAPI_BEACON_FRAME beacon;
      result = Get802Dot11Beacon(pEntry, &beacon);

      Print802(&beacon, FMT_OPTION_COLOR);
      exit(0);
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
