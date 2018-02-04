/** \file   vsidui.c
 * \brief   Native GTK3 VSID UI
 *
 * \author  Marco van den Heuvel <blackystardust68@yahoo.com>
 * \author  Bas Wassink <b.wassink@ziggo.nl>
 */

/*
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#include "vice.h"

#include <stdio.h>

#include "not_implemented.h"

#include "machine.h"
#include "psid.h"
#include "ui.h"
#include "uisidattach.h"
#include "uivsidwindow.h"
#include "vicii.h"

#include "vsidtuneinfowidget.h"

#include "vsidui.h"


void vsid_ui_close(void)
{
    NOT_IMPLEMENTED_WARN_ONLY();
}


/** \brief  Display tune author in the UI
 *
 * \param[in]   author  author name
 */
void vsid_ui_display_author(const char *author)
{
    vsid_tune_info_widget_set_author(author);
}


/** \brief  Display tune copyright info in the UI
 *
 * \param[in]   copright    copyright info
 */
void vsid_ui_display_copyright(const char *copyright)
{
    vsid_tune_info_widget_set_copyright(copyright);
}


/** \brief  Set IRQ type for the UI
 *
 * \param[in]   irq IRQ type
 */
void vsid_ui_display_irqtype(const char *irq)
{
    vsid_tune_info_widget_set_irq(irq);
}


/** \brief  Display tune name in the UI
 *
 * \param[in]   name    tune name
 */
void vsid_ui_display_name(const char *name)
{
    vsid_tune_info_widget_set_name(name);
}


/** \brief  Set number of tunes for the UI
 *
 * \param[in]   count   number of tunes
 */
void vsid_ui_display_nr_of_tunes(int count)
{
    vsid_tune_info_widget_set_tune_count(count);
}


/** \brief  Set SID model for the UI
 *
 * \param[in]   model   SID model
 */
void vsid_ui_display_sid_model(int model)
{
    vsid_tune_info_widget_set_model(model);
}


/** \brief  Set sync factor for the UI
 *
 * \param[in]   sync    sync factor
 */
void vsid_ui_display_sync(int sync)
{
    vsid_tune_info_widget_set_sync(sync);
}


/** \brief  Set run time of tune in the UI
 *
 * \param[in]   sec seconds of play time
 */
void vsid_ui_display_time(unsigned int sec)
{
    vsid_tune_info_widget_set_time(sec);
}


/** \brief  Set current tune number in the UI
 *
 * \param[in]   nr  tune number
 */
void vsid_ui_display_tune_nr(int nr)
{
    vsid_tune_info_widget_set_tune_current(nr);
}

/** \brief  Identify the canvas used to create a window
 *
 * \return  window index on success, -1 on failure
 */
static int identify_canvas(video_canvas_t *canvas)
{
    if (canvas != vicii_get_canvas()) {
        return -1;
    }

    return PRIMARY_WINDOW;
}


int vsid_ui_init(void)
{
    video_canvas_t *canvas = vicii_get_canvas();

    ui_vsid_window_init();
    ui_set_identify_canvas_func(identify_canvas);

    ui_create_toplevel_window(canvas);
    ui_display_toplevel_window(canvas->window_index);

    uisidattach_set_psid_init_func(psid_init_driver);
    uisidattach_set_psid_play_func(machine_play_psid);

    INCOMPLETE_IMPLEMENTATION();
    return 0;
}


/** \brief  Set driver info text for the UI
 *
 * \param[in]   driver_info_text    text with driver info (duh)
 */
void vsid_ui_setdrv(char *driver_info_text)
{
    vsid_tune_info_widget_set_driver(driver_info_text);
}


/** \brief  Set default tune number in the UI
 *
 * \param[in]   nr  tune number
 */
void vsid_ui_set_default_tune(int nr)
{
    vsid_tune_info_widget_set_tune_default(nr);
}

