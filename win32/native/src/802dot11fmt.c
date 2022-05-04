#include "../include/802dot11fmt.h"

#define __static static

// typedef VOID(*ie_print_handler)(__const WLANAPI_IE_BLOB *, DWORD);

// typedef struct _IE_PRINTER {
//   DWORD ieId;
//   ie_print_handler handler;
// } IE_PRINTER, *PIE_PRINTER;

// __const IE_PRINTER IE_FMT_REF[] = {
//   { 1, NULL }
// };

#define AsMAC(str, mac) sprintf(str, "%x:%x:%x:%x:%x:%x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5])

__static VOID __out_802_frame_bc_header(__const WLANAPI_BEACON_FRAME *_Frame, DWORD _Options);
__static VOID __out_802_frame_bc_body(__const WLANAPI_BEACON_FRAME *_Frame, DWORD _Options);
__static VOID __out_802_ie(__const PWLANAPI_IE_BLOB _Ie, DWORD _Options, BOOLEAN _End);

STRING __atov_ie_name(__const DWORD _IeId) {
#define CASE(x) case x: return #x;
#define CASE2(x, y) case x: return y;
  switch (_IeId) {
    CASE2(IE_SSID, "SSID")                               
    CASE2(IE_SUPPORTED_RATES, "Supported Rates")                    
    CASE(IE_FH_PARAMETER_SET)                   
    CASE(IE_DSSS_PARAMETER_SET)                 
    CASE(IE_CF_PARAMETER_SET)                   
    CASE(IE_TIM)                                
    CASE(IE_IBSS_PARAMETER_SET)                 
    CASE(IE_COUNTRY)                            
    CASE(IE_HOPPING_PATTERN_PARAMETERS)         
    CASE(IE_HOPPING_PATTERN_TABLE)              
    CASE(IE_REQUEST)                             
    CASE(IE_BSS_LOAD)                            
    CASE(IE_EDCA_PARAMETER_SET)                  
    CASE(IE_TSPEC)                               
    CASE(IE_TCLAS)                               
    CASE(IE_SCHEDULE)                            
    CASE(IE_CHALLENGE_TEXT)                      
    CASE(IE_POWER_CONSTRAINT)                    
    CASE(IE_POWER_CAPABILITY)                    
    CASE(IE_TPC_REQUEST)                         
    CASE(IE_TPC_REPORT)                          
    CASE(IE_SUPPORTED_CHANNELS)                  
    CASE(IE_CHANNEL_SWITCH_ANNOUNCEMENT)         
    CASE(IE_MEASUREMENT_REQUEST)                 
    CASE(IE_MEASUREMENT_REPORT)                  
    CASE(IE_QUIET)                               
    CASE(IE_IBSS_DFS)                            
    CASE(IE_ERP_INFORMATION)                     
    CASE(IE_TS_DELAY)                            
    CASE(IE_TCLAS_PROCESSING)                    
    CASE(IE_HT_CAPABILITIES)                     
    CASE(IE_QOS_CAPABILITY)                      
    CASE(IE_RSN)                                 
    CASE(IE_EXTENDED_SUPPORTED_RATES)            
    CASE(IE_AP_CHANNEL_REPORT)                   
    CASE(IE_NEIGHBOR_REPORT)                     
    CASE(IE_RCPI)                                
    CASE(IE_MOBILITY_DOMAIN)                     
    CASE(IE_FAST_BSS_TRANSITION)                 
    CASE(IE_TIMEOUT_INTERVAL)                    
    CASE(IE_RIC_DATA)                            
    CASE(IE_DSE_REGISTERED_LOCATION)             
    CASE(IE_SUPPORTED_OPERATING_CLASSES)         
    CASE(IE_EXTENDED_CHANNEL_SWITCH_ANNOUNCEMENT)
    CASE(IE_HT_OPERATION)                        
    CASE(IE_SECONDARY_CHANNEL_OFFSET)            
    CASE(IE_BSS_AVERAGE_ACCESS_DELAY)            
    CASE(IE_ANTENNA)                             
    CASE(IE_RSNI)                                
    CASE(IE_MEASUREMENT_PILOT_TRANSMISSION)      
    CASE(IE_BSS_AVAILABLE_ADMISSION_CAPACITY)    
    CASE(IE_BSS_AC_ACCESS_DELAY)                 
    CASE(IE_TIME_ADVERTISEMENT)                  
    CASE(IE_RM_ENABLED_CAPACITIES)               
    CASE(IE_MULTIPLE_BSSID)                      
    CASE(IE_20_40_BSS_COEXISTENCE)               
    CASE(IE_20_40_BSS_INTOLERANT_CHANNEL_REPORT) 
    CASE(IE_OVERLAPPING_BSS_SCAN_PARAMETERS)     
    CASE(IE_RIC_DESCRIPTOR)                      
    CASE(IE_MANAGEMENT_MIC)                      
    CASE(IE_EVENT_REQUEST)                       
    CASE(IE_EVENT_REPORT)                        
    CASE(IE_DIAGNOSTIC_REQUEST)                  
    CASE(IE_DIAGNOSTIC_REPORT)                   
    CASE(IE_LOCATION_PARAMETERS)                 
    CASE(IE_NONTRANSMITTED_BSSID_CAPABILITY)     
    CASE(IE_SSID_LIST)                           
    CASE(IE_MULTIPLE_BSSID_INDEX)                
    CASE(IE_FMS_DESCRIPTOR)                      
    CASE(IE_FMS_REQUEST)                         
    CASE(IE_FMS_RESPONSE)                        
    CASE(IE_QOS_TRAFFIC_CAPABILITY)              
    CASE(IE_BSS_MAX_IDLE_PERIOD)                 
    CASE(IE_TFS_REQUEST)                         
    CASE(IE_TFS_RESPONSE)                        
    CASE(IE_WNM_SLEEP_MODE)                      
    CASE(IE_TIM_BROADCAST_REQUEST)               
    CASE(IE_TIM_BROADCAST_RESPONSE)              
    CASE(IE_COLLOCATED_INTERFERENCE_REPORT)      
    CASE(IE_CHANNEL_USAGE)                       
    CASE(IE_TIME_ZONE)                           
    CASE(IE_DMS_REQUEST)                         
    CASE(IE_DMS_RESPONSE)                         
    CASE(IE_LINK_IDENTIFIER)                      
    CASE(IE_WAKEUP_SCHEDULE)                      
    CASE(IE_CHANNEL_SWITCH_TIMING)                
    CASE(IE_PTI_CONTROL)                          
    CASE(IE_TPU_BUFFER_STATUS)                    
    CASE(IE_INTERWORKING)                         
    CASE(IE_ADVERTISEMENT_PROTOCOL)               
    CASE(IE_EXPEDITED_BANDWIDTH_REQUEST)          
    CASE(IE_QOS_MAP_SET)                          
    CASE(IE_ROAMING_CONSORTIUM)                   
    CASE(IE_EMERGENCY_ALART_IDENTIFIER)           
    CASE(IE_MESH_CONFIGURATION)                   
    CASE(IE_MESH_ID)                              
    CASE(IE_MESH_LINK_METRIC_REPORT)              
    CASE(IE_CONGESTION_NOTIFICATION)              
    CASE(IE_MESH_PEERING_MANAGEMENT)              
    CASE(IE_MESH_CHANNEL_SWITCH_PARAMETERS)       
    CASE(IE_MESH_AWAKE_WINDOW)                    
    CASE(IE_BEACON_TIMING)                        
    CASE(IE_MCCAOP_SETUP_REQUEST)                 
    CASE(IE_MCCAOP_SETUP_REPLY)                   
    CASE(IE_MCCAOP_ADVERTISEMENT)                 
    CASE(IE_MCCAOP_TEARDOWN)                      
    CASE(IE_GANN)                                 
    CASE(IE_RANN)                                 
    CASE(IE_EXTENDED_CAPABILITIES)                
    CASE(IE_PREQ)                                 
    CASE(IE_PREP)                                 
    CASE(IE_PERR)                                 
    CASE(IE_PROXY_UPDATE)                         
    CASE(IE_PROXY_UPDATE_CONFIRMATION)            
    CASE(IE_AUTHENTICATED_MESH_PEERING_EXCHANGE)  
    CASE(IE_MIC)                                  
    CASE(IE_DESTINATION_URI)                      
    CASE(IE_UAPSD_COEXISTENCE)                    
    CASE(IE_MCCAOP_ADVERTISEMENT_OVERVIEW)        
    CASE(IE_VHT_CAPABILITIES)                     
    CASE(IE_VHT_OPERATION)                        
    CASE(IE_EXTENDED_BSS_LOAD)                    
    CASE(IE_WIDE_BANDWIDTH_CHANNEL_SWITCH)        
    CASE(IE_VHT_TRANSMIT_POWER_ENVELOPE)          
    CASE(IE_CHANNEL_SWITCH_WRAPPER)               
    CASE(IE_AID)                                  
    CASE(IE_QUIET_CHANNEL)                        
    CASE(IE_OPERATING_MODE_NOTIFICATION)          
    CASE2(IE_VENDOR_SPECIFIC, "Vendor Specific")                      
    CASE(IE_EXTENSION)                            
  }
#undef CASE
}

#define __ETH_FRAME_LINE_SEP \
"============================================================================\n"

#define __ETH_FRAME_TREE_HEADER __ETH_FRAME_LINE_SEP \
"[Frame] Ethernet - 802.11 (Management)\n" \
__ETH_FRAME_LINE_SEP

#define __ETH_VAR_NODE_FMT_COL \
"|   |- \033[91m%s\033[0m:         %s \033[90m[%s]\033[0m\n"
#define __ETH_VAR_NODE_FMT_END_COL \
"|   '- \033[91m%s\033[0m:         %s \033[90m[%s]\033[0m\n|\n"

#define __ETH_VAR_NODE_FMT \
"|   |- %s:         %s [%s]\n"
#define __ETH_VAR_NODE_FMT_END \
"|   '- %s:         %s [%s]\n|\n"

#define __ETH_FRAME_TREE_NODE_COL \
"|= \033[4;94m%s\033[0m\n"
#define __ETH_FRAME_TREE_NODE \
"|= %s\n"

#define __ETH_FRAME_TREE_NODE_COL_END \
"'= \033[4;94m%s\033[0m 0x00\n"
#define __ETH_FRAME_TREE_NODE_END \
"'= %s 0x00\n"

#define __ETH_NODE_IE_COL \
"|   |- \033[4;94m%s\033[0m \033[91mID=\033[0m%i \033[91mLen=\033[0m%i %s\n"
#define __ETH_NODE_IE \
"|   |- %s ID=%i Len=%i %s\n"

#define __ETH_NODE_IE_END_COL \
"|   '- \033[4;94m%s\033[0m \033[91mID=\033[0m%i \033[91mLen=\033[0m%i %s\n"
#define __ETH_NODE_IE_END \
"|   '- %s ID=%i Len=%i %s\n"

VOID __out_802_frame(__const WLANAPI_BEACON_FRAME *_Frame, DWORD _Options) {
  if (!_Frame) {
    printf("[-] The given frame is NULL.");
    return;
  }

  printf(__ETH_FRAME_TREE_HEADER);
  printf(_Options ? __ETH_FRAME_TREE_NODE_COL : __ETH_FRAME_TREE_NODE, "802.11 MAC Header");
  //out header
  __out_802_frame_bc_header(_Frame, _Options);
  printf(_Options ? __ETH_FRAME_TREE_NODE_COL : __ETH_FRAME_TREE_NODE, 
    _Frame->ieSSID.ieSize > 0 ? "802.11 Management - Beacon" : "802.11 Management - Probe Request");
  //out body
  __out_802_frame_bc_body(_Frame, _Options);
  printf(_Options ? __ETH_FRAME_TREE_NODE_COL_END : __ETH_FRAME_TREE_NODE_END, "FCS");
}

__static VOID __out_802_frame_bc_header(__const WLANAPI_BEACON_FRAME *_Frame, DWORD _Options) {
  if (!_Frame) {
    printf("[-] The given frame is NULL.");
    return;
  }
#define print_H(var, ...) printf(_Options ? var##_COL : var, __VA_ARGS__)
  print_H(__ETH_VAR_NODE_FMT, "Version     ", "0",     "0 Mask 0x03");
  print_H(__ETH_VAR_NODE_FMT, "Type        ",    "00",    "Management | 0 Mask 0x0C");
  print_H(__ETH_VAR_NODE_FMT, "SubType     ", "10000", "Beacon | 0 Mask 0x0F");

  print_H(__ETH_VAR_NODE_FMT, "FrameControl", "0x8000", "0-1");
  print_H(__ETH_VAR_NODE_FMT, "Duration    ", "0", "Microseconds | 2-3");
  print_H(__ETH_VAR_NODE_FMT, "Destination ", "ff:ff:ff:ff:ff:ff", "Ethernet Broadcast | 4-9");

  CHAR *str = (CHAR *)malloc(18*sizeof(CHAR));
  AsMAC(str, _Frame->header.ucSource);

  print_H(__ETH_VAR_NODE_FMT,     "Source      ", str, "10-15");
  print_H(__ETH_VAR_NODE_FMT_END, "BSSID       ", str, "15-21");
#undef print_H
}

__static VOID __out_802_frame_bc_body(__const WLANAPI_BEACON_FRAME *_Frame, DWORD _Options) {
#define print_H(var, ...) printf(_Options ? var##_COL : var, __VA_ARGS__)
  print_H(__ETH_VAR_NODE_FMT, "Timestamp       ", "0", "Not captured");
  CHAR *fmt = malloc(10*sizeof(CHAR));
  sprintf(fmt, "%i", _Frame->usInterval);
  print_H(__ETH_VAR_NODE_FMT, "BeaconInterval  ", fmt, "32-33");
  sprintf(fmt, "0x%x", _Frame->usCapabilities);
  print_H(__ETH_VAR_NODE_FMT, "CapabilityInfo  ", fmt, "");
  free(fmt);
#undef print_H

  PWLANAPI_IE_BLOB ie = NULL;
  DWORD index = 0;
  while (index < _Frame->ulIeLength) {
    ie = ConvertBlobToIE(_Frame->pIeDataBlob, index);
    index += ie->ieSize + 2;
    __out_802_ie(ie, _Options, index >= _Frame->ulIeLength);
  }
}

__static VOID __out_802_ie(__const PWLANAPI_IE_BLOB _Ie, DWORD _Options, BOOLEAN _End) {
#define CASE(ID, code) case ID: code
#define out(var, ...) \
  printf(_End ? (_Options ? var##_END_COL : var##_END) : (_Options ? var##_COL : var), __VA_ARGS__)
#define HP(_Ie, size, f0, f1, ...) \
  str = _Options ? f0 : f1; \
  fmt = malloc((size)*sizeof(CHAR)); \
  sprintf(fmt, str, __VA_ARGS__); \
  out(__ETH_NODE_IE, GetIETypeString(_Ie->ieId), _Ie->ieId, _Ie->ieSize, fmt); \
  free(fmt), fmt = NULL;

  CHAR *fmt = NULL;
  STRING str;
  switch (_Ie->ieId) {
    CASE(IE_SSID, {
      if (_Ie->ieSize == 0) {
        out(__ETH_NODE_IE, GetIETypeString(_Ie->ieId), _Ie->ieId, _Ie->ieSize, 
        _Options ? "\033[90mBroadcast SSID\033[0m (Frame is Probe Request)" : 
        "Broadcast SSID (Frame is Probe Request)");
      } else {
        HP(_Ie, _Ie->ieSize + 6, "\033[91mSSID=\033[0m%s", "SSID=%s", _Ie->pIelement)
        }
      break;
    })
    CASE(IE_VENDOR_SPECIFIC, {
      HP(_Ie, 45, "\033[91mOUI=\033[0m%x-%x-%x \033[91mData=\033[0m(%i bytes)", "OUI=%x:%x:%x Data=(%i bytes)",
      _Ie->pIelement[0], _Ie->pIelement[1], _Ie->pIelement[2], _Ie->ieSize)
      break;
    })

    default: {
      HP(_Ie, 26, "\033[91mData=\033[0m(%i bytes)", "Data=(%i bytes)", _Ie->ieSize)
      break;
    }
  }

#undef CASE
#undef HP
#undef out
}

#undef __ETH_FRAME_TREE_NODE_COL_END
#undef __ETH_FRAME_TREE_NODE_COL
#undef __ETH_FRAME_TREE_NODE_END
#undef __ETH_FRAME_TREE_NODE
#undef __ETH_FRAME_TREE_HEADER 
#undef __ETH_VAR_NODE_FMT_END_COL
#undef __ETH_VAR_NODE_FMT_COL 
#undef __ETH_VAR_NODE_FMT_END
#undef __ETH_VAR_NODE_FMT
#undef __ETH_FRAME_LINE_SEP
#undef __ETH_NODE_IE_END_COL
#undef __ETH_NODE_IE_END
#undef __ETH_NODE_IE_COL
#undef __ETH_NODE_IE