#ifndef OS_COMMON_H
#define OS_COMMON_H

#include <stdint.h>

// Declare C linkage
#define OS_C_ABI extern "C"

// Make sure the compiler realy inlines if we say so
#ifdef inline
#	undef inline
#endif // inline

// Force inline
#define OS_INLINE __attribute__((always_inline)) inline
// Pack structs
#define OS_PACKED __attribute__((packed))

typedef uint8_t byte_t;

typedef volatile byte_t * const pioreg_t;
typedef volatile byte_t ioreg_t;

typedef volatile uint16_t * const pioreg16_t;
typedef volatile uint16_t const ioreg16_t;

OS_INLINE
void panic() __attribute__((noreturn));

namespace os {

    constexpr int EINVAL = 1;

}

#endif // OS_COMMON_H
