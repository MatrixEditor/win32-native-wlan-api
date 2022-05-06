#include "../include/win32pcap.h"

DWORD __atop_pcap_gb_header(BYTE *_Data, __const DWORD _Offset) 
{
  DWORD i = _Offset;
  memset((VOID *)_Data, 0x00, PCAP_GLOBAL_H_LEN);
  _Data[i++] = 0xd4, _Data[i++] = 0xc3;
  _Data[i++] = 0xb2, _Data[i++] = 0xa1;
  _Data[i++] = 0x02; i++;
  _Data[i++] = 0x04; i+=9;
  _Data[i++] = 0xff, _Data[i++] = 0xff; i+=2;
  _Data[i] = 0x69; // type

  return ERROR_SUCCESS;
}

DWORD __atop_pcap_rd_header(BYTE *_Data, ULONG _PacketSize, __const DWORD _Offset) 
{
  DWORD i = _Offset;
  memset((VOID *)_Data, 0x00, PCAP_RECORD_H_LEN);

  time_t ts = time(NULL);
  _Data[i++] = ts      , _Data[i++] = ts >>  8, _Data[i++] = ts >> 16;
  _Data[i++] = ts >> 24, _Data[i++] = ts >> 32, _Data[i++] = ts >> 42;
  _Data[i++] = ts >> 48, _Data[i++] = ts >> 56;

  _Data[i++] = _PacketSize, _Data[i++] = _PacketSize >> 8;
  _Data[i++] = _PacketSize >> 16, _Data[i++] = _PacketSize >> 24;
  _Data[i++] = _PacketSize, _Data[i++] = _PacketSize >> 8;
  _Data[i++] = _PacketSize >> 16, _Data[i++] = _PacketSize >> 24;
  return ERROR_SUCCESS;
}

DWORD __atop_pcap_dump(WLANAPI_BEACON_FRAME *_Frame, FILE *_File)
{
  BYTE _Data[36] = { 0 };
  DWORD i = 0;

  _Data[i++] = 0x80, _Data[i++] = 0x00;
  i+=2; //skip duration
  memset((VOID *)(_Data + i), 0xff, 6); i+=6; //MAC
  memcpy((VOID *)(_Data + i), _Frame->header.ucBSSID, 6); i+=6;
  memcpy((VOID *)(_Data + i), _Frame->header.ucBSSID, 6); i+=8;
  
  ULONGLONG ts = _Frame->ullTimestamp;
  _Data[i++] = ts      , _Data[i++] = ts >>  8, _Data[i++] = ts >> 16;
  _Data[i++] = ts >> 24, _Data[i++] = ts >> 32, _Data[i++] = ts >> 40;
  _Data[i++] = ts >> 48, _Data[i++] = ts >> 56;

  USHORT iv = _Frame->usInterval;
  _Data[i++] = iv, _Data[i++] = iv >> 8;

  USHORT cp = _Frame->usCapabilities;
  _Data[i++] = cp, _Data[i++] = cp >> 8;

  fwrite(_Data, sizeof(CHAR), 36, _File);
  fwrite(_Frame->pIeDataBlob, sizeof(CHAR), _Frame->ulIeLength, _File);
  
  BYTE _End[4] = {0};
  fwrite(_End, sizeof(CHAR), 4, _File); 
}