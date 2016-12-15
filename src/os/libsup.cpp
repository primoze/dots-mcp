/*
 * Copyright 2016 Primoz Erjavec
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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

void __cxa_guard_abort (__guard *) { }


#ifdef __cplusplus
}
#endif

#endif
