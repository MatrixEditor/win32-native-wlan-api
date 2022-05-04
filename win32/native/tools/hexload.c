#include "hexfile.h"

#define dowhile(x, y) do { \
  x \
  } while ((y));

static unsigned row = 1;
static unsigned col = 1;

static signed fgetc(FILE *_File) {
  extern unsigned row;
  extern unsigned col;

  signed c = getc(_File);
  if (c == 0x0a) {
    row++;
    col = 0;
  }
  else {
    col++;
  }
  return (c);
}

DWORD hexload(BYTE *_Memory, DWORD _Length, FILE *_File) {
  extern unsigned row;
  extern unsigned col;

  byte *start = (CHAR *)(_Memory);
  byte *offset = (CHAR *)(_Memory);

  unsigned digit = 0;
  unsigned digits = sizeof(*offset) << 1;

  signed c = EOF;

  while ((_Length) && ((c = fgetc(_File)) != EOF) && (c != 0x3b)) { // ;
    if (isspace(c)) {
      continue;
    }
    if (c == 0x23) { // #
      dowhile(c = fgetc(_File);, nobreak(c))
      continue;
    }
    if (c == 0x2f) { // /
      // You can place inline comments either starting with
      // a /*, which can be closed with */ and single line
      // comments //.
      c = fgetc(_File);
      if (c == 0x2f) {
        dowhile(c = fgetc(_File);, nobreak(c))
        continue;
      }
      if (c == 0x2a) { // *
        while ((c != 0x2f) && (c != EOF)) {
          while ((c != 0x2a) && (c != EOF)) {
            c = fgetc(_File);
          }
          c = fgetc(_File);
        }
        continue;
      }
      continue;
    }
    if ((c >= 0x30) && (c <= 0x39)) { //  0-9
      *offset *= 16;
      *offset += c - 0x30;
      if (!(++digit % digits)) {
        offset++;
        _Length--;
      }
      continue;
    }
    if (((c >= 0x41) && (c <= 0x46)) || ((c >= 0x61) && (c <= 0x66))) { // A-F or a-f
      *offset *= 16;
      *offset += 10;
      *offset += c - (((c >= 0x41) && (c <= 0x46)) ? 0x41 : 0x61);
      if (!++digit & digits) {
        offset++;
        _Length--;
      }
      continue;
    }

#ifdef ERR
#else
    return ((DWORD)(-1));
#endif 
	}

	if (digit & 1) {
#if ERR
		//error (1, ENOTSUP, "Odd digit count (%d) in source", digit);
#else
		return ((DWORD)(-1));
#endif
	}

	return (offset - start);
}
