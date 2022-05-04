#include "../win32/native/include/win32pcap.h"

FILE *fp = NULL; 

VOID handleNotification(PWLAN_NOTIFICATION_DATA pData, PVOID pV) {
  EXTERN_C FILE *fp;
  fp = fopen(".\\example.pcap", "ab");
  BYTE header[PCAP_GLOBAL_H_LEN + 1] = { 0 };
  BYTE recH[PCAP_RECORD_H_LEN] = { 0 };

  PcapAddGlobalHeader(header, 0);
  fwrite(header, sizeof(CHAR), PCAP_GLOBAL_H_LEN + 1, fp);
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
        
        PcapAddRecordHeader(recH, PCAP_PACKET_LEN(&beacon), 0);
        fwrite(recH, sizeof(CHAR), PCAP_RECORD_H_LEN, fp);
        PcapDumpBeacon(&beacon, fp);
        fclose(fp);
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