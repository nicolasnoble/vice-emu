/** \file   archdep.c
 * \brief   Wrappers for architecture/OS-specific code
 *
 * I've decided to use GLib's use of the XDG specification and the standard
 * way of using paths on Windows. So some files may not be where the older
 * ports expect them to be. For example, vicerc will be in $HOME/.config/vice
 * now, not $HOME/.vice. -- compyx
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

#include "archdep.h"
#include "lib.h"
#include "log.h"


int archdep_init(int *argc, char **argv)
{
    return 0;
}
void archdep_shutdown(void)
{
    archdep_program_name_free();
    archdep_boot_path_free();
    archdep_user_cache_path_free();
    archdep_user_config_path_free();
    archdep_default_sysfile_pathlist_free();
}

