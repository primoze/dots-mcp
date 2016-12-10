
#include <stdlib.h>

void *operator new(size_t size) {
  return malloc(size);
}

void *operator new[](size_t size) {
  return malloc(size);
}
void operator delete(void* p) {
    free(p);
}
void operator delete[](void * ptr) {
  free(ptr);
}
void operator delete(void* p, unsigned int) {
    free(p);
}
void operator delete[](void* p, unsigned int) {
    free(p);
}

#ifndef _ICXXABI_H
#define _ICXXABI_H

#define ATEXIT_MAX_FUNCS    128

#ifdef __cplusplus
extern "C" {
#endif

void __cxa_pure_virtual(void) __attribute__ ((__noreturn__));
void __cxa_deleted_virtual(void) __attribute__ ((__noreturn__));

void __cxa_pure_virtual(void) {
  abort();
}

void __cxa_deleted_virtual(void) {
  abort();
}

__extension__ typedef int __guard __attribute__((mode (__DI__)));

int __cxa_guard_acquire(__guard *g) {
 return !*(char *)(g);
}

void __cxa_guard_release (__guard *g) {
 *(char *)g = 1;
}

void __cxa_guard_abort (__guard *) {}


#ifdef __cplusplus
}
#endif

#endif
