#pragma once

#define HAVE_STRERROR

static __attribute__((always_inline)) char *strtok(char *str, const char *delim) {
    register int n asm("t1") = 0x23;
    __asm__ volatile("" : "=r"(n) : "r"(n));
    return ((char *(*)(char *, const char *))0xa0)(str, delim);
}
