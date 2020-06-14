/** \file   dirmenupopup.c
 *  \brief  Create a menu to show a directory of a drive or tape deck
 *
 * FIXME: The current code depends way too much on internal/core code. The code
 *        to retrieve the current disk/tape image should be implemented
 *        somewhere in the core code, not here.
 *
 *
 *  \author Bas Wassink <b.wassink@ziggo.nl>
 *  \author Groepaz (groepaz@gmx.de>
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

#include <gtk/gtk.h>

#include "attach.h"
#include "autostart.h"
#include "csshelpers.h"
#include "debug_gtk3.h"
#include "diskimage.h"
#include "diskimage/fsimage.h"
#include "drive.h"
#include "drivetypes.h"
#include "imagecontents/diskcontents.h"
#include "lib.h"
#include "log.h"
#include "tape.h"
#include "util.h"
#include "vdrive/vdrive.h"
#include "widgethelpers.h"

#include "dirmenupopup.h"


/** \brief  Function to read the contents of an image
 *
 * FIXME:   Hiding the pointer-ness of a function is NOT a good idea
 */
static read_contents_func_type content_func;

/** \brief  Function to call when a file in the directory is selected */
static void (*response_func)(const char *, int);

/** \brief  Disk image being used
 *
 * FIXME:   Somehow pass this via the event handlers
 */
static const char *autostart_diskimage;


/** \brief  CSS style string to set the CBM font and remove padding
 */
#define MENULABEL_CSS \
    "label {\n" \
    "  font-family: \"C64 Pro Mono\";\n" \
    "  font-size: 16px;\n" \
    "  letter-spacing: 0;\n" \
    "  margin: -2px;\n" \
    "  border: 0;\n" \
    "  padding: 0;\n" \
    "}"

/** \brief  CSS style string to remove padding from menu items
 */
#define MENUITEM_CSS \
    "menuitem {\n" \
    "  margin: 0;\n" \
    "  border: 0;\n" \
    "  padding: 0;\n" \
    "}"


/** \brief  CSS provider used for directory entry GtkMenuItem labels */
static GtkCssProvider *menulabel_css_provider;

/** \brief  CSS provider used for directory entry GtkMenuItem's */
static GtkCssProvider *menuitem_css_provider;


/** \brief  Handler for the "activate" event of a menu item
 *
 * \param[in]   item    menu item triggering the event
 * \param[in]   data    index in the directory (0 = header)
 */
static void on_item_activate(GtkWidget *item, gpointer data)
{
    int index = GPOINTER_TO_INT(data);

    response_func(autostart_diskimage, index);
}


/** \brief  Create reusable CSS providers
 *
 * \return bool
 */
static gboolean create_css_providers(void)
{
    menulabel_css_provider = vice_gtk3_css_provider_new(MENULABEL_CSS);
    if (menulabel_css_provider == NULL) {
        return FALSE;
    }
    menuitem_css_provider = vice_gtk3_css_provider_new(MENUITEM_CSS);
    if (menuitem_css_provider == NULL) {
        return FALSE;
    }
    return TRUE;
}


/** \brief  Apply CSS style and margins to a directory listing item
 *
 * \param[in,out]   item    direct list item
 */
void dir_item_apply_style(GtkWidget *item)
{
    GtkWidget *label;

    g_object_set(item, "margin-top", 0, "margin-bottom", 0, NULL);
    label = gtk_bin_get_child(GTK_BIN(item));
    vice_gtk3_css_provider_add(label, menulabel_css_provider);
    vice_gtk3_css_provider_add(item, menuitem_css_provider);
}


/** \brief  Create a popup menu to select a file to autostart
 *
 * XXX: This is an UNHOLY MESS, and should be refactored
 *
 * \param[in]   dev         device index (0-3 for drives, < 0 for tape)
 * \param[in]   func        function to read image contents
 * \param[in]   response    function to call when an item has been selected
 *
 * \return  GtkMenu
 */
GtkWidget *dir_menu_popup_create(
        int dev,
        read_contents_func_type func,
        void (*response)(const char *, int))
{
    GtkWidget *menu;
    GtkWidget *item;
    char buffer[1024];
    image_contents_t *contents = NULL;
    image_contents_file_list_t *entry;
    char *utf8;
    char *tmp;
    int index;
#if 0
    GtkWidget *label;
#endif
    int blocks;

    /* TODO: drive 1? */
    unsigned int drive = 0;


    debug_gtk3("DEVICE = %d, DRIVE = %d", dev, drive);

    /* create style providers */
    if (!create_css_providers()) {
        debug_gtk3("failed to create CSS providers, borking");
        return NULL;
    }

    /* set callback functions */
    content_func = func;
    response_func = response;

    /* create new menu */
    menu = gtk_menu_new();

    if (dev >= 0) {
        /*
         * The following is complete horseshit, this needs to be implemented in
         * a function in drive/vdrive somehow. This much dereferencing in UI
         * code is not normal method.
         */

        debug_gtk3("DEV = %d.", dev);

        vdrive_t *vdrive = NULL;
        struct disk_image_s *diskimg = NULL;
        autostart_diskimage = NULL;

        debug_gtk3("Getting vdrive reference for unit #%d.", dev + DRIVE_UNIT_MIN);
        vdrive = file_system_get_vdrive(dev + DRIVE_UNIT_MIN, drive);
        if (vdrive == NULL) {
            debug_gtk3("failed: got NULL.");
        } else {
            debug_gtk3("OK, Getting disk image from vdrive instance.");
            diskimg = vdrive->image;
            if (diskimg == NULL) {
                debug_gtk3("failed: got NULL.");
            } else {
                debug_gtk3("OK, Getting fsimage from disk image.");
                autostart_diskimage = diskimg->media.fsimage->name;
                if (autostart_diskimage == NULL) {
                    debug_gtk3("failed: got NULL.");
                } else {
                    debug_gtk3("Got '%s'.", autostart_diskimage);
                }
            }
        }

       debug_gtk3("fsimage is %s.", autostart_diskimage);
    } else {
        debug_gtk3("Trying tape for some reason.");
        /* tape image */
        if (tape_image_dev1 == NULL) {
            item = gtk_menu_item_new_with_label("<<NO IMAGE ATTACHED>>");
            gtk_container_add(GTK_CONTAINER(menu), item);
            return menu;
        }
        autostart_diskimage = tape_image_dev1->name;
    }

    tmp = NULL;
    if (autostart_diskimage) {
        util_fname_split(autostart_diskimage, NULL, &tmp);
    }
    if (dev >= 0) {
        g_snprintf(buffer, 1024, "Directory of unit %d drive %u (%s):",
                   dev + DRIVE_UNIT_MIN, drive, tmp ? tmp : "n/a");
    } else {
        g_snprintf(buffer, 1024, "Directory of attached tape: (%s)",
            tmp ? tmp : "n/a");
    }
    item = gtk_menu_item_new_with_label(buffer);
    gtk_container_add(GTK_CONTAINER(menu), item);
    if (tmp) {
        lib_free(tmp);
    }

    debug_gtk3("Did we get some image?");
    if (autostart_diskimage != NULL) {
        /* read dir and add them as menu items */
        contents = content_func(autostart_diskimage);
        if (contents == NULL) {
            debug_gtk3("content reading function failed!");
            item = gtk_menu_item_new_with_label(
                    "Failed to read directory");
            gtk_container_add(GTK_CONTAINER(menu), item);
        } else {
            debug_gtk3("Getting disk name & ID:");
            /* DISK name & ID */

            tmp = image_contents_to_string(contents, 0);
            utf8 = (char *)vice_gtk3_petscii_to_utf8((unsigned char *)tmp, 1);
            item = gtk_menu_item_new_with_label(utf8);

#if 0
            g_object_set(item, "margin-top", 0,
                    "margin-bottom", 0, NULL);
            label = gtk_bin_get_child(GTK_BIN(item));
            vice_gtk3_css_provider_add(label, menulabel_css_provider);
            vice_gtk3_css_provider_add(item, menuitem_css_provider);
#endif
            dir_item_apply_style(item);

            gtk_container_add(GTK_CONTAINER(menu), item);
            lib_free(tmp);
            lib_free(utf8);

            /* add separator */
            item = gtk_separator_menu_item_new();
            gtk_container_add(GTK_CONTAINER(menu), item);

            /* add files */
            index = 0;
            for (entry = contents->file_list; entry != NULL;
                    entry = entry->next) {

                tmp = image_contents_file_to_string(entry, 0);
                utf8 = (char *)vice_gtk3_petscii_to_utf8((unsigned char *)tmp, 0);
                item = gtk_menu_item_new_with_label(utf8);
#if 0
                g_object_set(item, "margin-top", 0, "margin-bottom", 0, NULL);
                label = gtk_bin_get_child(GTK_BIN(item));
                vice_gtk3_css_provider_add(label, menulabel_css_provider);
                vice_gtk3_css_provider_add(item, menuitem_css_provider);
#endif
                dir_item_apply_style(item);

                gtk_container_add(GTK_CONTAINER(menu), item);
                g_signal_connect(item, "activate",
                        G_CALLBACK(on_item_activate), GINT_TO_POINTER(index));
                index++;
                lib_free(tmp);
                lib_free(utf8);
            }

            /* add BLOCKS FREE. */
            blocks = contents->blocks_free;
            if (blocks >= 0) {
                tmp = lib_msprintf("%d BLOCKS FREE.", contents->blocks_free);
                item = gtk_menu_item_new_with_label(tmp);

                /* move this into separate function: */
                dir_item_apply_style(item);
                gtk_container_add(GTK_CONTAINER(menu), item);
                g_free(tmp);
            }
        }
        if (contents != NULL) {
            image_contents_destroy(contents);
        }
    } else {
        debug_gtk3("autostart_diskimage is NULL");
        item = gtk_menu_item_new_with_label("<<NO IMAGE ATTACHED>>");
        gtk_container_add(GTK_CONTAINER(menu), item);
    }
    gtk_widget_show_all(GTK_WIDGET(menu));

    return menu;
}
