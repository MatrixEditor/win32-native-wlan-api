#include "../win32/native/include/win32wlan.h"

#define PROG_BANNER "\
============================================================================\n\
                      WLAN-Interface listing v1\n\
============================================================================\n"

int main(int argc, char const *argv[]) {
  printf(PROG_BANNER);

  HANDLE hClient;
  DWORD error;
  DWORD size;
  PWLAN_INTERFACE_INFO_LIST list;
  PWLAN_INTERFACE_INFO info;

  if ((error = GetSession(&hClient)) != ERROR_SUCCESS) {
    printf("[-] Stopped at Error: code=%i\n", error);
    return error;
  }

  if ((error = NETGetInterfaces(hClient, &list)) != ERROR_SUCCESS) {
    printf("[-] Stopped at Error: code=%i\n", error);
    CloseSession(hClient);
    return error;
  }

  if ((size = list->dwNumberOfItems) == 0) {
    printf("[-] Found 0 WLAN-Interfaces: Capturing is not possible\n");
    CloseSession(hClient);
    return ERROR_SUCCESS;
  }

  printf("[+] Found %i WLAN-Interfaces\n", size);
  for (DWORD i = 0; i < size; i++) {
    info = &list->InterfaceInfo[i];

    __const CHAR *desc = GetIfaceDescription(info);
    printf("  <%i> - %s\n", i, desc);
  }

  wlanapi_free(list);
  CloseSession(hClient);
  return ERROR_SUCCESS;
}

#ifdef PROG_BANNER
  #undef PROG_BANNER  
#endif
