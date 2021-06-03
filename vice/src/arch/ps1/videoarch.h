#pragma once

#include "types.h"
#include "video.h"

#define NUM_AVAILABLE_COLORS	0x100

struct video_canvas_s {
    struct video_canvas_s *next; /* linked list */
    unsigned int initialized;
    unsigned int created;
    unsigned int width, height, depth, bytes_per_line;
    unsigned int use_triple_buffering;
    struct video_render_config_s *videoconfig;
    struct draw_buffer_s *draw_buffer;
    struct viewport_s *viewport;
    struct geometry_s *geometry;
    struct palette_s *palette;
    struct video_draw_buffer_callback_s *video_draw_buffer_callback;
    int current_fullscreen;
    int window_left;
    int window_top;
    int waiting_for_resize;
};
typedef struct video_canvas_s video_canvas_t;

#define CANVAS_USES_TRIPLE_BUFFERING(c) (c->use_triple_buffering)

/* ------------------------------------------------------------------------- */

struct _color_def {
    unsigned short red;
    unsigned short green;
    unsigned short blue;
    unsigned char dither;
};
typedef struct _color_def color_def_t;

/* ------------------------------------------------------------------------- */

void enable_text(void);
void disable_text(void);

void video_ack_vga_mode(void);
int video_in_gfx_mode(void);

void canvas_set_border_color(struct video_canvas_s *canvas, BYTE color);
