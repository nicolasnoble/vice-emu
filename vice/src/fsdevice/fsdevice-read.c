/*
 * fsdevice-read.c - File system device.
 *
 * Written by
 *  Andreas Boose <viceteam@t-online.de>
 *
 * Based on old code by
 *  Teemu Rantanen <tvr@cs.hut.fi>
 *  Jarkko Sonninen <sonninen@lut.fi>
 *  Jouko Valta <jopi@stekt.oulu.fi>
 *  Olaf Seibert <rhialto@falu.nl>
 *  Andre Fachat <a.fachat@physik.tu-chemnitz.de>
 *  Ettore Perazzoli <ettore@comm2000.it>
 *  pottendo <pottendo@gmx.net>
 *
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
#include <string.h>

#include "archdep.h"
#include "cbmdos.h"
#include "fileio.h"
#include "fsdevice-filename.h"
#include "fsdevice-read.h"
#include "fsdevice-resources.h"
#include "fsdevicetypes.h"
#include "ioutil.h"
#include "lib.h"
#include "tape.h"
#include "types.h"
#include "vdrive.h"

/* #define REL_DEBUG */

#ifdef REL_DEBUG
# define DBG(x) log_debug x
# include "log.h"
#else
# define DBG(x)
#endif

static int command_read(bufinfo_t *bufinfo, uint8_t *data)
{
    if (bufinfo->tape->name) {
        if (bufinfo->buflen > 0) {
            *data = *bufinfo->bufp++;
            bufinfo->buflen--;
        } else {
            /* If we are already at an EOF state, check next read, next stream
               may be available */
            if (bufinfo->iseof) {
                *data = 0xc7;
                bufinfo->iseof = !tape_read(bufinfo->tape,
                                            &(bufinfo->buffered), 1);
                bufinfo->isbuffered = 1;
                if (bufinfo->iseof) {
                    return SERIAL_EOF;
                }
            }
            /* If this is our first read, read in first byte */
            if (!bufinfo->isbuffered) {
                bufinfo->iseof = !tape_read(bufinfo->tape,
                                            &(bufinfo->buffered), 1);
                /* XXX We shouldn't get an EOF at this point, or can we? */
            }
            /* Place it in the output field */
            *data = bufinfo->buffered;
            /* Read the next buffer; if nothing read, set EOF signal */
            bufinfo->iseof = !tape_read(bufinfo->tape, &(bufinfo->buffered), 1);
            /* Indicate we have something in the buffer for the next read */
            bufinfo->isbuffered = 1;
            /* If the EOF was signaled, return a CBM EOF */
            if (bufinfo->iseof) {
                return SERIAL_EOF;
            }
            /* If not, return OK */
            return SERIAL_OK;

#if 0
            if (tape_read(bufinfo->tape, data, 1) != 1) {
                *data = 0xc7;
                return SERIAL_EOF;
            }
#endif
        }
        return SERIAL_OK;
    } else {
        if (bufinfo->fileio_info) {
            /* If we are already at an EOF state, check next read, next stream
               may be available */
            if (bufinfo->iseof) {
                *data = 0xc7;
                bufinfo->iseof = !tape_read(bufinfo->tape, &(bufinfo->buffered), 1);
                bufinfo->isbuffered = 1;
                if (bufinfo->iseof) {
                    return SERIAL_EOF;
                }
            }
            /* If this is our first read, read in first byte */
            if (!bufinfo->isbuffered) {
                bufinfo->iseof = !fileio_read(bufinfo->fileio_info, &(bufinfo->buffered), 1);
                /* We shouldn't get an EOF at this point */
                /* Check for errors */
                if (fileio_ferror(bufinfo->fileio_info)) {
                    return SERIAL_ERROR;
                }
            }
            /* Place it in the output field */
            *data = bufinfo->buffered;
            /* Read the next buffer; if nothing read, set EOF signal */
            bufinfo->iseof = !fileio_read(bufinfo->fileio_info, &(bufinfo->buffered), 1);
            /* Check for errors */
            if (fileio_ferror(bufinfo->fileio_info)) {
                return SERIAL_ERROR;
            }
            /* Indicate we have something in the buffer for the next read */
            bufinfo->isbuffered = 1;
            /* If the EOF was signaled, return a CBM EOF */
            if (bufinfo->iseof) {
                return SERIAL_EOF;
            }
            /* If not, return OK */
            return SERIAL_OK;

#if 0
            unsigned int len;

            len = fileio_read(bufinfo->info, data, 1);

            if (fileio_ferror(bufinfo->info)) {
                return SERIAL_ERROR;
            }

            if (len == 0) {
                *data = 0xc7;
                return SERIAL_EOF;
            }
            return SERIAL_OK;
#endif
        }
    }

    return FLOPPY_ERROR;
}

void fsdevice_relative_pad_record(bufinfo_t *bufinfo)
{
    if (bufinfo->record_is_dirty) {
        uint8_t filler = 0x00;

        /*
         * Mixing reading and writing of a single record isn't
         * allowed on a real drive, but try to support it anyway.
         */
        if (bufinfo->isbuffered) {
            fileio_seek(bufinfo->fileio_info, -1, SEEK_CUR);
            bufinfo->position_in_record--;
            bufinfo->isbuffered = 0;
        }

        /*
         * Fill the remainder of the record, from the current
         * position to the end, with 00.
         */
        while (bufinfo->position_in_record < bufinfo->reclen) {
            fileio_write(bufinfo->fileio_info, &filler, 1);
            bufinfo->position_in_record++;
        }

        bufinfo->record_is_dirty = 0;
    }
}

int fsdevice_relative_switch_record(vdrive_t *vdrive, bufinfo_t *bufinfo,
                                    int record, int pos)
{
    int rec_len = bufinfo->reclen;
    int fserror = CBMDOS_IPE_OK;
    unsigned int file_off;

    DBG(("fsdevice_relative_switch_record: rec_len=%d %d.%d",
            rec_len, record, pos));

    if (rec_len == 0) {
        fsdevice_error(vdrive, CBMDOS_IPE_NO_RECORD);
        return SERIAL_ERROR;
    } else if (pos >= rec_len) {
        fsdevice_error(vdrive, CBMDOS_IPE_OVERFLOW);
        return SERIAL_ERROR;
    }

    /*
     * If we get here for the first time, calculate how many
     * records there are in the file.
     */
    if (bufinfo->num_records <= 0) {
        off_t nbytes;
        fileio_seek(bufinfo->fileio_info, 0, SEEK_SET);
        nbytes = fileio_get_bytes_left(bufinfo->fileio_info);
        bufinfo->num_records = (int)((nbytes + bufinfo->reclen - 1) /
                               bufinfo->reclen);
        DBG(("fsdevice_relative_switch_record: num_records=%d",
            bufinfo->num_records));
    }

    file_off = record * rec_len + pos;

    /*
     * If we switch to a DIFFERENT record, the current one is finished
     * and we need to mark the end of the record as such.
     */
    if (record != bufinfo->current_record) {
        fsdevice_relative_pad_record(bufinfo);
    }

    fileio_seek(bufinfo->fileio_info, file_off, SEEK_SET);
    bufinfo->isbuffered = 0;

    if (record >= bufinfo->num_records) {
        /*
         * Don't actually extend the file yet.
         * That happens when the user writes a byte.
         */

        if (record > 0) {
            fserror = CBMDOS_IPE_NO_RECORD;
            bufinfo->current_record_length = 0;
        }

        /*
         * What error should we give if ALSO pos > 0?
         */
    }

    bufinfo->current_record = record;
    bufinfo->position_in_record = pos;
    bufinfo->iseof = 0;

    /*
     * Detect the length of the new current record.
     * Just wastefully read the whole thing byte by byte,
     * and remember where the last non-00 byte is.
     */
    if (fserror == CBMDOS_IPE_OK) {
        int testpos;

        /* Records can never be completely empty. */
        bufinfo->current_record_length = pos + 1;

        for (testpos = pos; testpos < bufinfo->reclen; testpos++) {
            uint8_t testbyte;
            int len;

            len = fileio_read(bufinfo->fileio_info, &testbyte, 1);

            if (len == 1 && testbyte != 0) {
                bufinfo->current_record_length = testpos + 1;
            }
        }

        fileio_seek(bufinfo->fileio_info, file_off, SEEK_SET);
        DBG(("fsdevice_relative_switch_record: current_record_length=%d",
                bufinfo->current_record_length));
    }

    if (fserror != CBMDOS_IPE_OK) {
        fsdevice_error(vdrive, fserror);
        return SERIAL_ERROR;
    }

    return SERIAL_OK;
}

static int relative_read(vdrive_t *vdrive, bufinfo_t *bufinfo, uint8_t *data)
{
    if (bufinfo->current_record >= bufinfo->num_records) {
        *data = 0x0d;
        DBG(("relative_read: store '%c' %02x CBMDOS_IPE_NO_RECORD", *data, *data));
        fsdevice_error(vdrive, CBMDOS_IPE_NO_RECORD);
        return SERIAL_EOF;
    }

    /*
     * Reading past one record gets us to the next (unlike writing).
     */
    if (bufinfo->iseof) {
        int err = fsdevice_relative_switch_record(vdrive, bufinfo, bufinfo->current_record + 1, 0);
        DBG(("relative_read: iseof, skip to next record"));
        if (err) {
            return SERIAL_OK;
        }
    }

    /*
     * If we switch from writing to reading, there must have been an
     * UNLISTEN in between. Since we have no callback for it,
     * check it in this way.
     */
#if 1
    if (bufinfo->record_is_dirty) {
        int err = fsdevice_relative_switch_record(vdrive, bufinfo, bufinfo->current_record + 1, 0);
        DBG(("relative_read: record_is_dirty, switching to read, skip to next record"));
        if (err) {
            return SERIAL_OK;
        }
    }
#endif

    /* If this is our first read, read in first byte */
    if (!bufinfo->isbuffered) {
        if (bufinfo->position_in_record < bufinfo->current_record_length) {
            DBG(("relative_read: !isbuffered, read a byte"));
            bufinfo->iseof = !fileio_read(bufinfo->fileio_info, &(bufinfo->buffered), 1);
            bufinfo->position_in_record++;
        } else {
            *data = 0x0d;
            return SERIAL_ERROR;
        }
        /* We shouldn't get an EOF at this point */
        /* Check for errors */
        if (fileio_ferror(bufinfo->fileio_info)) {
            *data = 0x0d;
            return SERIAL_ERROR;
        }
    }

    /* Place it in the output field */
    *data = bufinfo->buffered;
    DBG(("relative_read: store '%c' %02x", *data, *data));

    if (bufinfo->position_in_record < bufinfo->current_record_length) {
        /* DBG(("relative_read: record not exhausted (%d < %d), read a byte to buffer", bufinfo->position_in_record, bufinfo->current_record_length)); */
        /* Read the next buffer; if nothing read, set EOF signal */
        bufinfo->iseof = !fileio_read(bufinfo->fileio_info, &(bufinfo->buffered), 1);
        bufinfo->position_in_record++;
        /* Check for errors */
        if (fileio_ferror(bufinfo->fileio_info)) {
            return SERIAL_ERROR;
        }
        /* Indicate we have something in the buffer for the next read */
        bufinfo->isbuffered = 1;
    } else {
        DBG(("relative_read: record exhausted, set iseof and !isbuffered"));
        bufinfo->iseof = 1;
        bufinfo->isbuffered = 0;
    }

    /* If the EOF was signaled, return a CBM EOF */
    if (bufinfo->iseof) {
        DBG(("relative_read: return SERIAL_EOF"));
        return SERIAL_EOF;
    }

    /* If not, return OK */
    return SERIAL_OK;
}

static void command_directory_get(vdrive_t *vdrive, bufinfo_t *bufinfo,
                                  uint8_t *data, unsigned int secondary)
{
    int i, l, f, statrc;
    unsigned long blocks;
    char *direntry;
    size_t filelen;
    unsigned int isdir;
    fileio_info_t *finfo = NULL;
    unsigned int format = 0;
    char *buf;

    buf = lib_malloc(ioutil_maxpathlen());

    bufinfo->bufp = bufinfo->name;

    if (fsdevice_convert_p00_enabled[(vdrive->unit) - 8]) {
        format |= FILEIO_FORMAT_P00;
    }
    if (!fsdevice_hide_cbm_files_enabled[vdrive->unit - 8]) {
        format |= FILEIO_FORMAT_RAW;
    }

    /*
     * Find the next directory entry and return it as a CBM
     * directory line.
     */

    /* first test if dirmask is needed - maybe this should be
       replaced by some regex functions... */
    f = 1;
    do {
        uint8_t *p;
        finfo = NULL;

        direntry = ioutil_readdir(bufinfo->ioutil_dir);

        if (direntry == NULL) {
            break;
        }

        finfo = fileio_open(direntry, bufinfo->dir, format,
                            FILEIO_COMMAND_STAT | FILEIO_COMMAND_FSNAME,
                            FILEIO_TYPE_PRG, NULL);

        if (finfo == NULL) {
            continue;
        }

        bufinfo->type = finfo->type;

        if (bufinfo->dirmask[0] == '\0') {
            break;
        }

        l = (int)strlen(bufinfo->dirmask);

        for (p = finfo->name, i = 0;
             *p && bufinfo->dirmask[i] && i < l; i++) {
            if (bufinfo->dirmask[i] == '?') {
                p++;
            } else if (bufinfo->dirmask[i] == '*') {
                if (!(bufinfo->dirmask[i + 1])) {
                    f = 0;
                    break;
                } /* end mask */
                while (*p && (*p != bufinfo->dirmask[i + 1])) {
                    p++;
                }
            } else {
                if (*p != bufinfo->dirmask[i]) {
                    break;
                }
                p++;
            }
            if ((!*p) && (!(bufinfo->dirmask[i + 1]))) {
                f = 0;
                break;
            }
        }
        if (f > 0) {
            fileio_close(finfo);
        }
    } while (f);

    if (direntry != NULL) {
        uint8_t *p = bufinfo->name;

        strcpy(buf, bufinfo->dir);
        strcat(buf, FSDEV_DIR_SEP_STR);
        strcat(buf, direntry);

        /* Line link, Length and spaces */

        *p++ = 1;
        *p++ = 1;

        statrc = ioutil_stat(buf, &filelen, &isdir);
        if (statrc == 0) {
            blocks = (filelen + 253) / 254;
        } else {
            blocks = 0;   /* this file can't be opened */
        }

        if (blocks > 0xffff) {
            blocks = 0xffff; /* Limit file size to 16 bits.  */
        }

        SET_LO_HI(p, blocks);

        if (blocks < 10) {
            *p++ = ' ';
        }
        if (blocks < 100) {
            *p++ = ' ';
        }
        if (blocks < 1000) {
            *p++ = ' ';
        }

        /*
         * Filename
         */

        *p++ = '"';
        
        fsdevice_limit_namelength(vdrive, finfo->name);

        for (i = 0; finfo->name[i] && (*p = finfo->name[i]); ++i, ++p) {
        }

        *p++ = '"';
        for (; i < 16; i++) {
            *p++ = ' ';
        }

        if (isdir != 0) {
            *p++ = ' '; /* normal file */
            *p++ = 'D';
            *p++ = 'I';
            *p++ = 'R';
        } else {
            if (blocks) {
                *p++ = ' '; /* normal file */
            } else {
                *p++ = '*'; /* splat file */
            }
            switch (bufinfo->type) {
                case CBMDOS_FT_DEL:
                    *p++ = 'D';
                    *p++ = 'E';
                    *p++ = 'L';
                    break;
                case CBMDOS_FT_SEQ:
                    *p++ = 'S';
                    *p++ = 'E';
                    *p++ = 'Q';
                    break;
                case CBMDOS_FT_PRG:
                    *p++ = 'P';
                    *p++ = 'R';
                    *p++ = 'G';
                    break;
                case CBMDOS_FT_USR:
                    *p++ = 'U';
                    *p++ = 'S';
                    *p++ = 'R';
                    break;
                case CBMDOS_FT_REL:
                    *p++ = 'R';
                    *p++ = 'E';
                    *p++ = 'L';
                    break;
            }
        }

        if (ioutil_access(buf, IOUTIL_ACCESS_W_OK)) {
            *p++ = '<'; /* read-only file */
        }

        *p = '\0';        /* to allow strlen */

        /* some (really very) old programs rely on the directory
           entry to be 32 Bytes in total (incl. nullbyte) */
        l = (int)strlen((char *)(bufinfo->name + 4)) + 4;
        while (l < 31) {
            *p++ = ' ';
            l++;
        }

        *p++ = '\0';

        bufinfo->buflen = (int)(p - bufinfo->name);
    } else {
        uint8_t *p = bufinfo->name;

        /* EOF => End file */

        *p++ = 1;
        *p++ = 1;
        *p++ = 255; /* 65535 blocks free */
        *p++ = 255;
        memcpy(p, "BLOCKS FREE.", 12);
        p += 12;
        memset(p, ' ', 13);
        p += 13;

        memset(p, 0, 3);
        bufinfo->buflen = 32;
        bufinfo->eof++;
    }

    if (finfo != NULL) {
        fileio_close(finfo);
    }

    lib_free(buf);
}


static int command_directory(vdrive_t *vdrive, bufinfo_t *bufinfo,
                             uint8_t *data, unsigned int secondary)
{
    if (bufinfo->ioutil_dir == NULL) {
        return FLOPPY_ERROR;
    }

    if (bufinfo->buflen <= 0) {
        if (bufinfo->eof) {
            *data = 0xc7;
            return SERIAL_EOF;
        }
        command_directory_get(vdrive, bufinfo, data, secondary);
    }

    *data = *bufinfo->bufp++;
    bufinfo->buflen--;
    /* Generate CBM EOF */
    if (bufinfo->buflen <= 0) {
        if (bufinfo->eof) {
            return SERIAL_EOF;
        }
    }

    return SERIAL_OK;
}

int fsdevice_read(vdrive_t *vdrive, uint8_t *data, unsigned int secondary)
{
    bufinfo_t *bufinfo = &(fsdevice_dev[vdrive->unit - 8].bufinfo[secondary]);

    if (secondary == 15) {
        return fsdevice_error_get_byte(vdrive, data);
    }

    switch (bufinfo->mode) {
        case Write:
        case Append:
            return FLOPPY_ERROR;
        case Read:
            return command_read(bufinfo, data);
        case Relative:
            return relative_read(vdrive, bufinfo, data);
        case Directory:
            return command_directory(vdrive, bufinfo, data, secondary);
    }
    return FLOPPY_ERROR;
}
