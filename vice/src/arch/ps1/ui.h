#pragma once

#include "types.h"
#include "uiapi.h"

void ui_show_text(const char *title, const char *text);
void ui_main(char hotkey);
void ui_set_warp_status(int status);
void ui_dispatch_events(void);
void ui_display_speed(float percent, float framerate, int warp_flag);
