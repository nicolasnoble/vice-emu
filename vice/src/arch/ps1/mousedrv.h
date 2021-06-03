#pragma once

#include "types.h"

int mousedrv_resources_init(void);
int mousedrv_cmdline_options_init(void);
void mousedrv_init(void);

void mousedrv_mouse_changed(void);

BYTE mousedrv_get_x(void);
BYTE mousedrv_get_y(void);

extern int _mouse_available;
extern int _mouse_x, _mouse_y;
extern int _mouse_coords_dirty;
