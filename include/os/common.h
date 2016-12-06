#ifndef OS_COMMON_H
#define OS_COMMON_H

#include <stdint.h>

// Declare C linkage
#define OS_C_ABI extern "C"
// Force inline
#define OS_INLINE __attribute__((always_inline)) inline

typedef uint8_t byte_t;
typedef volatile byte_t * const ioreg_t;

#endif // OS_COMMON_H
