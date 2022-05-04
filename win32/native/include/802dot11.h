/**
 * @file 802dot11.h
 * @author MatrixEditor
 * 
 * @brief ...
 * 
 * @version 0.1
 * @date 2022-05-03
 * 
 * @copyright Copyright (c) 2022
 * @link https://mrncciew.com/2014/10/08/802-11-mgmt-beacon-frame/
 * @link https://howiwifi.com/2020/07/13/802-11-frame-types-and-formats/
 * @link https://www.oreilly.com/library/view/80211-wireless-networks/0596100523/ch04.html
 * 
 */

#if !defined(_WIN32_IEEE80211_H_)
#define _WIN32_IEEE80211_H_

#define IE_SSID                                 (0)
#define IE_SUPPORTED_RATES                      (1)
#define IE_FH_PARAMETER_SET                     (2)
#define IE_DSSS_PARAMETER_SET                   (3)
#define IE_CF_PARAMETER_SET                     (4)
#define IE_TIM                                  (5)
#define IE_IBSS_PARAMETER_SET                   (6)
#define IE_COUNTRY                              (7)
#define IE_HOPPING_PATTERN_PARAMETERS           (8)
#define IE_HOPPING_PATTERN_TABLE                (9)
#define IE_REQUEST                              (10)
#define IE_BSS_LOAD                             (11)
#define IE_EDCA_PARAMETER_SET                   (12)
#define IE_TSPEC                                (13)
#define IE_TCLAS                                (14)
#define IE_SCHEDULE                             (15)
#define IE_CHALLENGE_TEXT                       (16)
// 17 to 31 are reserved
#define IE_POWER_CONSTRAINT                     (32)
#define IE_POWER_CAPABILITY                     (33)
#define IE_TPC_REQUEST                          (34)
#define IE_TPC_REPORT                           (35)
#define IE_SUPPORTED_CHANNELS                   (36)
#define IE_CHANNEL_SWITCH_ANNOUNCEMENT          (37)
#define IE_MEASUREMENT_REQUEST                  (38)
#define IE_MEASUREMENT_REPORT                   (39)
#define IE_QUIET                                (40)
#define IE_IBSS_DFS                             (41)
#define IE_ERP_INFORMATION                      (42)
#define IE_TS_DELAY                             (43)
#define IE_TCLAS_PROCESSING                     (44)
#define IE_HT_CAPABILITIES                      (45)
#define IE_QOS_CAPABILITY                       (46)
// 47 is reserved
#define IE_RSN                                  (48)
// 49 is reserved
#define IE_EXTENDED_SUPPORTED_RATES             (50)
#define IE_AP_CHANNEL_REPORT                    (51)
#define IE_NEIGHBOR_REPORT                      (52)
#define IE_RCPI                                 (53)
#define IE_MOBILITY_DOMAIN                      (54)
#define IE_FAST_BSS_TRANSITION                  (55)
#define IE_TIMEOUT_INTERVAL                     (56)
#define IE_RIC_DATA                             (57)
#define IE_DSE_REGISTERED_LOCATION              (58)
#define IE_SUPPORTED_OPERATING_CLASSES          (59)
#define IE_EXTENDED_CHANNEL_SWITCH_ANNOUNCEMENT (60)
#define IE_HT_OPERATION                         (61)
#define IE_SECONDARY_CHANNEL_OFFSET             (62)
#define IE_BSS_AVERAGE_ACCESS_DELAY             (63)
#define IE_ANTENNA                              (64)
#define IE_RSNI                                 (65)
#define IE_MEASUREMENT_PILOT_TRANSMISSION       (66)
#define IE_BSS_AVAILABLE_ADMISSION_CAPACITY     (67)
#define IE_BSS_AC_ACCESS_DELAY                  (68)
#define IE_TIME_ADVERTISEMENT                   (69)
#define IE_RM_ENABLED_CAPACITIES                (70)
#define IE_MULTIPLE_BSSID                       (71)
#define IE_20_40_BSS_COEXISTENCE                (72)
#define IE_20_40_BSS_INTOLERANT_CHANNEL_REPORT  (73)
#define IE_OVERLAPPING_BSS_SCAN_PARAMETERS      (74)
#define IE_RIC_DESCRIPTOR                       (75)
#define IE_MANAGEMENT_MIC                       (76)
// 77 is reserved
#define IE_EVENT_REQUEST                        (78)
#define IE_EVENT_REPORT                         (79)
#define IE_DIAGNOSTIC_REQUEST                   (80)
#define IE_DIAGNOSTIC_REPORT                    (81)
#define IE_LOCATION_PARAMETERS                  (82)
#define IE_NONTRANSMITTED_BSSID_CAPABILITY      (83)
#define IE_SSID_LIST                            (84)
#define IE_MULTIPLE_BSSID_INDEX                 (85)
#define IE_FMS_DESCRIPTOR                       (86)
#define IE_FMS_REQUEST                          (87)
#define IE_FMS_RESPONSE                         (88)
#define IE_QOS_TRAFFIC_CAPABILITY               (89)
#define IE_BSS_MAX_IDLE_PERIOD                  (90)
#define IE_TFS_REQUEST                          (91)
#define IE_TFS_RESPONSE                         (92)
#define IE_WNM_SLEEP_MODE                       (93)
#define IE_TIM_BROADCAST_REQUEST                (94)
#define IE_TIM_BROADCAST_RESPONSE               (95)
#define IE_COLLOCATED_INTERFERENCE_REPORT       (96)
#define IE_CHANNEL_USAGE                        (97)
#define IE_TIME_ZONE                            (98)
#define IE_DMS_REQUEST                          (99)
#define IE_DMS_RESPONSE                         (100)
#define IE_LINK_IDENTIFIER                      (101)
#define IE_WAKEUP_SCHEDULE                      (102)
// 103 is reserved
#define IE_CHANNEL_SWITCH_TIMING                (104)
#define IE_PTI_CONTROL                          (105)
#define IE_TPU_BUFFER_STATUS                    (106)
#define IE_INTERWORKING                         (107)
#define IE_ADVERTISEMENT_PROTOCOL               (108)
#define IE_EXPEDITED_BANDWIDTH_REQUEST          (109)
#define IE_QOS_MAP_SET                          (110)
#define IE_ROAMING_CONSORTIUM                   (111)
#define IE_EMERGENCY_ALART_IDENTIFIER           (112)
#define IE_MESH_CONFIGURATION                   (113)
#define IE_MESH_ID                              (114)
#define IE_MESH_LINK_METRIC_REPORT              (115)
#define IE_CONGESTION_NOTIFICATION              (116)
#define IE_MESH_PEERING_MANAGEMENT              (117)
#define IE_MESH_CHANNEL_SWITCH_PARAMETERS       (118)
#define IE_MESH_AWAKE_WINDOW                    (119)
#define IE_BEACON_TIMING                        (120)
#define IE_MCCAOP_SETUP_REQUEST                 (121)
#define IE_MCCAOP_SETUP_REPLY                   (122)
#define IE_MCCAOP_ADVERTISEMENT                 (123)
#define IE_MCCAOP_TEARDOWN                      (124)
#define IE_GANN                                 (125)
#define IE_RANN                                 (126)
// 67 to 126 are reserved
#define IE_EXTENDED_CAPABILITIES                (127)
// 128 to 129 are reserved
#define IE_PREQ                                 (130)
#define IE_PREP                                 (131)
#define IE_PERR                                 (132)
// 133 to 136 are reserved
#define IE_PROXY_UPDATE                         (137)
#define IE_PROXY_UPDATE_CONFIRMATION            (138)
#define IE_AUTHENTICATED_MESH_PEERING_EXCHANGE  (139)
#define IE_MIC                                  (140)
#define IE_DESTINATION_URI                      (141)
#define IE_UAPSD_COEXISTENCE                    (142)
// 143 to 173 are reserved
#define IE_MCCAOP_ADVERTISEMENT_OVERVIEW        (174)
// 175 to 190 are reserved
#define IE_VHT_CAPABILITIES                     (191)
#define IE_VHT_OPERATION                        (192)
#define IE_EXTENDED_BSS_LOAD                    (193)
#define IE_WIDE_BANDWIDTH_CHANNEL_SWITCH        (194)
#define IE_VHT_TRANSMIT_POWER_ENVELOPE          (195)
#define IE_CHANNEL_SWITCH_WRAPPER               (196)
#define IE_AID                                  (197)
#define IE_QUIET_CHANNEL                        (198)
#define IE_OPERATING_MODE_NOTIFICATION          (199)
// 200 to 220 are reserved
#define IE_VENDOR_SPECIFIC                      (221)
// 222 to 254 are reserved
#define IE_EXTENSION                            (255)

/** 
* @brief Type value for management (layer-2) frames 
*/
#define IEEE80211_TYPE_MGMT  0x0000

#define IS_DEFINED_IE(x) (!(IsReserverd_IE(x)))

#define IsReserved_Helper(x, s, e) ((x) > s && (x) < e)
#define IsReserverd_IE(x) (IsReserved_Helper(x, 142, 173) || IsReserved_Helper(x, 174, 191) || \
  IsReserved_Helper(x, 199, 221) || IsReserved_Helper(x, 221, 255) || IsReserved_Helper(x, 132, 137) || \
  IsReserved_Helper(x, 127, 130) || IsReserved_Helper(x, 16, 32) || (x) == 103 || (x) == 47 || \
  (x) == 49)


#endif // _WIN32_IEEE80211_H_
