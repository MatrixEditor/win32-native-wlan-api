#if !defined(_IEEE_802DOT11_FMT_H_)
#define _IEEE_802DOT11_FMT_H_

#include "win32wlan.h"

#define FMT_OPTION_COLOUR 1
#define FMT_OPTION_DEFAULT 0

/**
 * @brief A small wrapper for constant character arrays. (also known as strings)
 */
typedef __const char *STRING;

/**
 * @brief A simple function to pretty print the given beacon frame out to the 
 * console.
 * 
 * @param _Frame The frame to print
 * @param _Options If color is requested on output this should be set with this
 *                 variable
 * @name Print802
 */
VOID __cdecl __out_802_frame(__const WLANAPI_BEACON_FRAME *_Frame, DWORD _Options);
#define Print802(_pFrame, _Options) \
  __out_802_frame((__const WLANAPI_BEACON_FRAME *)_pFrame, (DWORD)_Options)

/**
 * @brief Returns the qualified name to the given information element.
 * 
 * @param _IeId id of the information element
 * @return [const char *] the name of the information element type 
 * @name GetIETypeString
 */
STRING __cdecl __atov_ie_name(__const DWORD _IeId);
#define GetIETypeString(_IeId) __atov_ie_name((__const DWORD)_IeId)

/**
 * @brief ...
 * 
 * @param _Ie 
 * @param _Options 
 * @return VOID 
 */
VOID __cdecl __out_ie_fmt(__const WLANAPI_IE_BLOB *_Ie, DWORD _Options);
#define PrintIE(_pIe, _Options) \
  __out_ie_fmt((__const WLANAPI_IE_BLOB *)_pIe, (DWORD )_Options)

#endif // _IEEE_802DOT11_FMT_H_
