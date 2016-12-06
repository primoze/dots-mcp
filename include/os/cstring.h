
#ifndef OS_CSTRING_H
#define OS_CSTRING_H

#include <os/common.h>

#include <avr/pgmspace.h>

namespace os {

typedef char* cstring_t;

class __flash_string_t;
typedef const __flash_string_t* flash_cstring_t;


}

#define OS_FSTR(str) (reinterpret_cast<const os::__flash_string_t*>(PSTR(str)))


#endif // OS_CSTRING_H
