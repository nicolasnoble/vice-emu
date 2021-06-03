#pragma once

#include "kbd.h"

typedef enum {
    JOYDEV_NONE,
    JOYDEV_NUMPAD,
    JOYDEV_KEYSET1,
    JOYDEV_KEYSET2,
    JOYDEV_HW1,
    JOYDEV_HW2
} joystick_device_t;

extern int joystick_port_map[2];

int joy_arch_init(void);
void joystick_close(void);
int joystick_arch_init_resources(void);
int joystick_init_cmdline_options(void);
void joystick_update(void);
int joystick_handle_key(kbd_code_t kcode, int pressed);
