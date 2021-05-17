TARGET = c64
TYPE = ps-exe

ARCH_SRCS = \
common/syscalls/printf.s \
common/crt0/crt0.s \
archdep.c \
c128ui.c \
c64dtvui.c \
c64scui.c \
c64ui.c \
cbm2ui.c \
cbm5x0ui.c \
console.c \
joy.c \
kbd.c \
main.c \
mousedrv.c \
petui.c \
plus4ui.c \
scpu64ui.c \
ui.c \
uimon.c \
uistatusbar.c \
vic20ui.c \
video.c \
vsidui.c \
vsyncarch.c \

EXTRA_SRCS = \
posix-stubs.c \

SHARED_SRCS = \
../shared/archdep_cbmfont.c \
../shared/archdep_extra_title_text.c \
../shared/archdep_filename_parameter.c \
../shared/archdep_get_current_drive.c \
../shared/archdep_get_runtime_info.c \
../shared/archdep_icon_path.c \
../shared/archdep_is_haiku.c \
../shared/archdep_is_macos_bindist.c \
../shared/archdep_is_windows_nt.c \
../shared/archdep_join_paths.c \
../shared/archdep_kbd_get_host_mapping.c \
../shared/archdep_list_drives.c \
../shared/archdep_make_backup_filename.c \
../shared/archdep_quote_parameter.c \
../shared/archdep_quote_unzip.c \
../shared/archdep_rename.c \
../shared/archdep_require_vkbd.c \
../shared/archdep_rtc_get_centisecond.c \
../shared/archdep_sanitize_filename.c \
../shared/archdep_set_current_drive.c \
../shared/archdep_sound.c \
../shared/archdep_user_cache_path.c \
../shared/archdep_user_config_path.c \
../shared/archdep_usleep.c \

VICE_SRCS = \
../../alarm.c \
../../attach.c \
../../autostart.c \
../../autostart-prg.c \
../../cbmdos.c \
../../cbmimage.c \
../../charset.c \
../../clipboard.c \
../../clkguard.c \
../../cmdline.c \
../../color.c \
../../debug.c \
../../dma.c \
../../embedded.c \
../../fixpoint.c \
../../gcr.c \
../../info.c \
../../init.c \
../../initcmdline.c \
../../interrupt.c \
../../kbdbuf.c \
../../machine-bus.c \
../../machine.c \
../../main.c \
../../mainlock.c \
../../midi.c \
../../ps2mouse.c \
../../ram.c \
../../rawnet.c \
../../screenshot.c \
../../sound.c \
../../tick.c \
../../traps.c \
../../usleep.c \
../../vicefeatures.c \
../../vsync.c \
../../zipcode.c \

C64_SRCS = \
../../c64/c64_256k.c \
../../c64/c64bus.c \
../../c64/c64.c \
../../c64/c64cia1.c \
../../c64/c64cia2.c \
../../c64/c64-cmdline-options.c \
../../c64/c64cpusc.c \
../../c64/c64datasette.c \
../../c64/c64drive.c \
../../c64/c64embedded.c \
../../c64/c64export.c \
../../c64/c64fastiec.c \
../../c64/c64gluelogic.c \
../../c64/c64iec.c \
../../c64/c64io.c \
../../c64/c64keyboard.c \
../../c64/c64meminit.c \
../../c64/c64memlimit.c \
../../c64/c64-memory-hacks.c \
../../c64/c64memrom.c \
../../c64/c64memsc.c \
../../c64/c64parallel.c \
../../c64/c64pla.c \
../../c64/c64printer.c \
../../c64/c64-resources.c \
../../c64/c64rom.c \
../../c64/c64romset.c \
../../c64/c64rsuser.c \
../../c64/c64scmodel.c \
../../c64/c64sound.c \
../../c64/c64video.c \
../../c64/patchrom.c \
../../c64/plus256k.c \
../../c64/plus60k.c \

SRCS = $(ARCH_SRCS) $(EXTRA_SRCS) $(SHARED_SRCS) $(VICE_SRCS) $(C64_SRCS)

CPPFLAGS += -I../..
CPPFLAGS += -I../../c64
CPPFLAGS += -I../../c64/cart
CPPFLAGS += -I../../core
CPPFLAGS += -I../../datasette
CPPFLAGS += -I../../diskimage
CPPFLAGS += -I../../drive
CPPFLAGS += -I../../drive/iec/c64exp
CPPFLAGS += -I../../fsdevice
CPPFLAGS += -I../../hvsc
CPPFLAGS += -I../../imagecontents
CPPFLAGS += -I../../joyport
CPPFLAGS += -I../../lib/p64
CPPFLAGS += -I../../monitor
CPPFLAGS += -I../../rs232drv
CPPFLAGS += -I../../rtc
CPPFLAGS += -I../../tape
CPPFLAGS += -I../../tapeport
CPPFLAGS += -I../../samplerdrv
CPPFLAGS += -I../../sid
CPPFLAGS += -I../../userport
CPPFLAGS += -I../../vdrive
CPPFLAGS += -I../../vicii
CPPFLAGS += -I../../viciisc
CPPFLAGS += -I../../viciivsid
CPPFLAGS += -I../../video
CPPFLAGS += -I../shared
CPPFLAGS += -Ipseudoposix

include common.mk
