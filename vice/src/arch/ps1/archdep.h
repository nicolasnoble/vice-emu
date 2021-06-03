#pragma once

#include "archapi.h"

/* Filesystem dependant operators.  */
#define FSDEVICE_DEFAULT_DIR   "."
#define FSDEV_DIR_SEP_STR      "/"
#define FSDEV_DIR_SEP_CHR      '/'
#define FSDEV_EXT_SEP_STR      "."
#define FSDEV_EXT_SEP_CHR      '.'

/* Path separator.  */
#define ARCHDEP_FINDPATH_SEPARATOR_CHAR         ';'
#define ARCHDEP_FINDPATH_SEPARATOR_STRING       ";"

/* Modes for fopen().  */
#define MODE_READ              "r"
#define MODE_READ_TEXT         "r"
#define MODE_READ_WRITE        "r+"
#define MODE_WRITE             "w"
#define MODE_WRITE_TEXT        "w"
#define MODE_APPEND            "w"
#define MODE_APPEND_READ_WRITE "a+"

/* Printer default devices.  */
#define ARCHDEP_PRINTER_DEFAULT_DEV1 ""
#define ARCHDEP_PRINTER_DEFAULT_DEV2 ""
#define ARCHDEP_PRINTER_DEFAULT_DEV3 ""

/* Video chip scaling.  */
#define ARCHDEP_VICII_DSIZE   0
#define ARCHDEP_VICII_DSCAN   0
#define ARCHDEP_VICII_HWSCALE 0
#define ARCHDEP_VDC_DSIZE     1
#define ARCHDEP_VDC_DSCAN     1
#define ARCHDEP_VDC_HWSCALE   0
#define ARCHDEP_VIC_DSIZE     0
#define ARCHDEP_VIC_DSCAN     0
#define ARCHDEP_VIC_HWSCALE   0
#define ARCHDEP_CRTC_DSIZE    0
#define ARCHDEP_CRTC_DSCAN    0
#define ARCHDEP_CRTC_HWSCALE  0
#define ARCHDEP_TED_DSIZE     0
#define ARCHDEP_TED_DSCAN     0
#define ARCHDEP_TED_HWSCALE   0

/* Video chip double buffering.  */
#define ARCHDEP_VICII_DBUF 0
#define ARCHDEP_VDC_DBUF   0
#define ARCHDEP_VIC_DBUF   0
#define ARCHDEP_CRTC_DBUF  0
#define ARCHDEP_TED_DBUF   0

/* Default location of raw disk images.  */
#define ARCHDEP_RAWDRIVE_DEFAULT "cdrom:"

/* Access types */
#define ARCHDEP_R_OK 4
#define ARCHDEP_W_OK 2
#define ARCHDEP_X_OK 1
#define ARCHDEP_F_OK 0

/* Standard line delimiter.  */
#define ARCHDEP_LINE_DELIMITER "\n"

/* Ethernet default device */
#define ARCHDEP_ETHERNET_DEFAULT_DEVICE ""

/* No key symcode.  */
#define ARCHDEP_KEYBOARD_SYM_NONE 0
