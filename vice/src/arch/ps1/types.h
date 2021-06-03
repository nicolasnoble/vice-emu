#pragma once

#include "vice.h"

#include <stdint.h>

typedef uint8_t BYTE;
typedef int8_t SIGNED_CHAR;
typedef uint16_t WORD;
typedef int16_t SWORD;
typedef uint32_t DWORD;
typedef int32_t SDWORD;

typedef DWORD CLOCK;
/* Maximum value of a CLOCK.  */
#define CLOCK_MAX (~((CLOCK)0))

#define REGPARM1
#define REGPARM2
#define REGPARM3

typedef void DIR;
struct dirent {
    char d_name[32];
};
