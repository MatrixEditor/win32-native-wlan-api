#if !defined(_HEXFILE_IO_H_)
#define _HEXFILE_IO_H_

#include <stdio.h>
#include <windows.h>

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#define HEXIO_DIGITS "0123456789ABCDEF"

/**
 * @brief read a file and convert hexadecimal octets to binary bytes then
 * store them in consecutive memory locations up to a given length;
 * return the actual number of bytes stored;
 * 
 * digits may be consecutive or separated by white space or comment
 * text; a colon terminates a frame, to allow multiple frames in a
 * on one file;
 * 
 * @param _Memory the memory pointer (BYTE)
 * @param _Length max length of bytes stored
 * @param _File the file pointer
 * @return [unsigned long] the amount of bytes stored
 */
DWORD __cdecl hexload(BYTE *_Memory, DWORD _Length, FILE *_File);

/**
 * @brief print memory as a series of hexadecimal octets seperated by
 * character c; normally, character c will be HEX_EXTENDER as
 * defined in number.h;
 * 
 * for example, hexout (memory, 6, ':', ';', stdout) would print:
 *    00:B0:52:00:00:01;
 * 
 * @param _Memory the memory pointer (uint8_t | byte)
 * @param _Length max length of bytes stored
 * @param _Sep separator
 * @param _End end character
 * @param _File the file pointer
 */
DWORD __cdecl hexout(VOID *_Memory, DWORD _Length, CHAR _Sep, CHAR _End, FILE *_File);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // _HEXFILE_IO_H_