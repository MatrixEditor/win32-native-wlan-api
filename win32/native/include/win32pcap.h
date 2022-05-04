/**
 * @file win32pcap.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <time.h>
#include <Windows.h>

#include "win32wlan.h"

/**
 * @brief The file has a global header containing some global information followed 
 * by zero or more records for each captured packet. 
 * 
 * Structure:
 *  + magic_number: used to detect the file format itself and the byte ordering. The 
 *    writing application writes 0xa1b2c3d4 with it's native byte ordering format into 
 *    this field. The reading application will read either 0xa1b2c3d4 (identical) or 
 *    0xd4c3b2a1 (swapped). If the reading application reads the swapped 0xd4c3b2a1 value, 
 *    it knows that all the following fields will have to be swapped too.
 * 
 *  + version_major, version_minor: the version number of this file format (current 
 *    version is 2.4)
 * 
 *  + thiszone: the correction time in seconds between GMT (UTC) and the local timezone 
 *    of the following packet header timestamps. Examples: If the timestamps are in GMT 
 *    (UTC), thiszone is simply 0. If the timestamps are in Central European time (Amsterdam, 
 *    Berlin, …) which is GMT + 1:00, thiszone must be -3600. In practice, time stamps are 
 *    always in GMT, so thiszone is always 0.
 * 
 *  + sigfigs: in theory, the accuracy of time stamps in the capture; in practice, all tools
 *    set it to 0
 *
 *  + snaplen: the "snapshot length" for the capture (typically 65535 or even more, but might
 *    be limited by the user), see: incl_len vs. orig_len below
 * 
 *  + network: link-layer header type, specifying the type of headers at the beginning of the 
 *    packet (e.g. 1 for Ethernet, see tcpdump.org's link-layer header types page for details)
 *
 * @link https://wiki.wireshark.org/Development/LibpcapFileFormat
 */
#define PCAP_GLOBAL_H_LEN 0x18

/**
 * @brief Each captured packet starts with a record header.
 * 
 * Structure:
 *  + ts_sec: the date and time when this packet was captured. This value is in seconds since 
 *    January 1, 1970 00:00:00 GMT; this is also known as a UN*X time_t. You can use the ANSI C time() 
 *    function from time.h to get this value, but you might use a more optimized way to get this 
 *    timestamp value. If this timestamp isn't based on GMT (UTC), use thiszone from the global 
 *    header for adjustments.
 * 
 *  + ts_usec: in regular pcap files, the microseconds when this packet was captured, as an offset 
 *    to ts_sec. In nanosecond-resolution files, this is, instead, the nanoseconds when the packet 
 *    was captured, as an offset to ts_sec warning
 * 
 *  + incl_len: the number of bytes of packet data actually captured and saved in the file. This value 
 *    should never become larger than orig_len or the snaplen value of the global header.
 * 
 *  + orig_len: the length of the packet as it appeared on the network when it was captured. If incl_len 
 *    and orig_len differ, the actually saved packet size was limited by snaplen.
 * 
 * @link https://wiki.wireshark.org/Development/LibpcapFileFormat
 */
#define PCAP_RECORD_H_LEN 0x10

/**
 * @brief Determine the packet length:
 *    -> 36 = mandatory fields length
 *    -> ssidLength + 2 = ieBlob
 *    -> ratesLength + 2 = ieBlob
 *    -> other ieBlob length
 */
#define PCAP_PACKET_LEN(_pPacket) \
  (DWORD)(36+((_pPacket)->ulIeLength))

/** 
 * @brief Adds the global PCAP-Header to the given data.
 * 
 * @param _Data The data where the header should be added to
 * @return [unsigned long] ERROR_SUCCESS if no errors occurred. 
 * @name PcapAddGlobalHeader
 */
DWORD __cdecl __atop_pcap_gb_header(BYTE *_Data, __const DWORD _Offset);
#define PcapAddGlobalHeader(_pData, _Offset) __atop_pcap_gb_header((BYTE *)_pData, _Offset)

/**
 * @brief Adds Record (Packet) Header to the given data
 * 
 * @param _Data The data where the header should be added to 
 * @param _PacketSize the size of the packet which will be written next.
 * @return [unsigned long] ERROR_SUCCESS if no errors occurred. 
 * @name PcapAddRecordHeader
 */
DWORD __cdecl __atop_pcap_rd_header(BYTE *_Data, ULONG _PacketSize, __const DWORD _Offset);
#define PcapAddRecordHeader(_pData, _PacketSize, _Offset) \
  __atop_pcap_rd_header((BYTE *)_pData, (ULONG)_PacketSize, _Offset)


DWORD __atop_pcap_dump(WLANAPI_BEACON_FRAME *_Frame, FILE *_File);
#define PcapDumpBeacon(_pFrame, _pFile) \
  __atop_pcap_dump((WLANAPI_BEACON_FRAME *)_pFrame, (FILE *)_pFile)

