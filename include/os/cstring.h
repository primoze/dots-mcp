
#ifndef OS_CSTRING_H
#define OS_CSTRING_H

#include <os/common.h>

#include <avr/pgmspace.h>

namespace os {

typedef const char* cstring_t;

class __flash_cstring_t;
typedef const __flash_cstring_t* flash_cstring_t;


}

#define OS_MK_FSTR(str) reinterpret_cast<os::flash_cstring_t>(PSTR(str))
#define OS_FSTR(str) reinterpret_cast<os::flash_cstring_t>(str)


#endif // OS_CSTRING_H
