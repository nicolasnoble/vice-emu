#pragma once

#include "types.h"

void kbd_arch_init(void);

signed long kbd_arch_keyname_to_keynum(char *keyname);
const char *kbd_arch_keynum_to_keyname(signed long keynum);
void kbd_initialize_numpad_joykeys(int *joykeys);

#define KBD_C64_SYM_US  "dos_sym.vkm"
#define KBD_C64_POS     "dos_pos.vkm"

#define KBD_INDEX_C64_DEFAULT   KBD_INDEX_C64_POS

/* Keymap definition structure.  */
typedef struct {
    BYTE row;
    BYTE column;
    int vshift;
} keyconv;

typedef enum {
    K_NONE, K_ESC, K_1, K_2, K_3, K_4, K_5, K_6, K_7, K_8, K_9, K_0, K_MINUS,
    K_EQUAL, K_BS, K_TAB, K_Q, K_W, K_E, K_R, K_T, K_Y, K_U, K_I, K_O, K_P,
    K_LEFTBR, K_RIGHTBR, K_ENTER, K_LEFTCTRL, K_A, K_S, K_D, K_F, K_G, K_H,
    K_J, K_K, K_L, K_SEMICOLON, K_GRAVE, K_NUMSGN, K_LEFTSHIFT, K_BACKSLASH,
    K_Z, K_X, K_C, K_V, K_B, K_N, K_M, K_COMMA, K_PERIOD, K_SLASH,
    K_RIGHTSHIFT, K_KPMULT, K_LEFTALT, K_SPACE, K_CAPSLOCK, K_F1, K_F2, K_F3,
    K_F4, K_F5, K_F6, K_F7, K_F8, K_F9, K_F10, K_NUMLOCK, K_SCROLLOCK, K_KP7,
    K_KP8, K_KP9, K_KPMINUS, K_KP4, K_KP5, K_KP6, K_KPPLUS, K_KP1, K_KP2,
    K_KP3, K_KP0, K_KPDOT, K_SYSREQ, K_85, K_LTGT, K_F11, K_F12, K_HOME, K_UP,
    K_PGUP, K_LEFT, K_RIGHT, K_END, K_DOWN, K_PGDOWN, K_INS, K_DEL,
    K_KPENTER, K_RIGHTCTRL, K_PAUSE, K_PRTSCR, K_KPDIV, K_RIGHTALT, K_BREAK,
    K_LEFTW95, K_RIGHTW95
} kbd_code_t;

extern BYTE _kbd_extended_key_tab[256];

int kbd_init(int num, ...);
void kbd_install(void);
void kbd_uninstall(void);
void kbd_flush_commands(void);
void kbd_set_freeze_function(void (*f)(void));
const char *kbd_code_to_string(kbd_code_t kcode);

#undef COMMON_KBD
