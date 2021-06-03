TOPDIR := $(abspath $(dir $(abspath $(lastword $(MAKEFILE_LIST))))/../..)

USE_FUNCTION_SECTIONS = false

TARGET = c64
TYPE = ps-exe

CPPFLAGS += \
-DNOFLOATINGPOINT \
-I$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/libc/include \
-I$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/os/include \
-I$(TOPDIR)/arch/ps1/nugget/tests/uC-sdk-glue \
-I$(TOPDIR)/arch/ps1/pseudoposix \
-I$(TOPDIR)/arch/ps1 \
-I$(TOPDIR)/ \
-I$(TOPDIR)/c64/ \
-I$(TOPDIR)/drive/ \
-I$(TOPDIR)/raster \
-I$(TOPDIR)/sid \
-I$(TOPDIR)/tape \
-I$(TOPDIR)/vdrive/ \
-I$(TOPDIR)/vicii \

libc64 = \
$(TOPDIR)/c64/c64-cmdline-options.c \
$(TOPDIR)/c64/c64-resources.c \
$(TOPDIR)/c64/c64-snapshot.c \
$(TOPDIR)/c64/c64.c \
$(TOPDIR)/c64/c64_256k.c \
$(TOPDIR)/c64/c64acia1.c \
$(TOPDIR)/c64/c64bus.c \
$(TOPDIR)/c64/c64cia1.c \
$(TOPDIR)/c64/c64cia2.c \
$(TOPDIR)/c64/c64datasette.c \
$(TOPDIR)/c64/c64drive.c \
$(TOPDIR)/c64/c64export.c \
$(TOPDIR)/c64/c64fastiec.c \
$(TOPDIR)/c64/c64iec.c \
$(TOPDIR)/c64/c64io.c \
$(TOPDIR)/c64/c64keyboard.c \
$(TOPDIR)/c64/c64mem.c \
$(TOPDIR)/c64/c64meminit.c \
$(TOPDIR)/c64/c64memlimit.c \
$(TOPDIR)/c64/c64memrom.c \
$(TOPDIR)/c64/c64memsnapshot.c \
$(TOPDIR)/c64/c64parallel.c \
$(TOPDIR)/c64/c64pla.c \
$(TOPDIR)/c64/c64printer.c \
$(TOPDIR)/c64/c64rom.c \
$(TOPDIR)/c64/c64romset.c \
$(TOPDIR)/c64/c64rsuser.c \
$(TOPDIR)/c64/c64sound.c \
$(TOPDIR)/c64/c64tpi.c \
$(TOPDIR)/c64/c64video.c \
$(TOPDIR)/c64/digimax.c \
$(TOPDIR)/c64/georam.c \
$(TOPDIR)/c64/mmc64.c \
$(TOPDIR)/c64/patchrom.c \
$(TOPDIR)/c64/plus256k.c \
$(TOPDIR)/c64/plus60k.c \
$(TOPDIR)/c64/psid.c \
$(TOPDIR)/c64/ramcart.c \
$(TOPDIR)/c64/reloc65.c \
$(TOPDIR)/c64/reu.c \
$(TOPDIR)/c64/tfe.c \

libc64cart = \
$(TOPDIR)/c64/cart/actionreplay3.c \
$(TOPDIR)/c64/cart/actionreplay4.c \
$(TOPDIR)/c64/cart/actionreplay.c \
$(TOPDIR)/c64/cart/atomicpower.c \
$(TOPDIR)/c64/cart/c64cart.c \
$(TOPDIR)/c64/cart/c64cartmem.c \
$(TOPDIR)/c64/cart/comal80.c \
$(TOPDIR)/c64/cart/crt.c \
$(TOPDIR)/c64/cart/delaep256.c \
$(TOPDIR)/c64/cart/delaep64.c \
$(TOPDIR)/c64/cart/delaep7x8.c \
$(TOPDIR)/c64/cart/epyxfastload.c \
$(TOPDIR)/c64/cart/expert.c \
$(TOPDIR)/c64/cart/final.c \
$(TOPDIR)/c64/cart/generic.c \
$(TOPDIR)/c64/cart/ide64.c \
$(TOPDIR)/c64/cart/kcs.c \
$(TOPDIR)/c64/cart/magicformel.c \
$(TOPDIR)/c64/cart/mikroass.c \
$(TOPDIR)/c64/cart/retroreplay.c \
$(TOPDIR)/c64/cart/rexep256.c \
$(TOPDIR)/c64/cart/ross.c \
$(TOPDIR)/c64/cart/stardos.c \
$(TOPDIR)/c64/cart/stb.c \
$(TOPDIR)/c64/cart/supergames.c \
$(TOPDIR)/c64/cart/supersnapshot.c \
$(TOPDIR)/c64/cart/zaxxon.c \

libdriveiec = \
$(TOPDIR)/drive/iec/cia1571d.c \
$(TOPDIR)/drive/iec/cia1581d.c \
$(TOPDIR)/drive/iec/glue1571.c \
$(TOPDIR)/drive/iec/iec-cmdline-options.c \
$(TOPDIR)/drive/iec/iec-resources.c \
$(TOPDIR)/drive/iec/iec.c \
$(TOPDIR)/drive/iec/iecrom.c \
$(TOPDIR)/drive/iec/memiec.c \
$(TOPDIR)/drive/iec/via1d1541.c \
$(TOPDIR)/drive/iec/wd1770.c \

libdriveiecieee = \
$(TOPDIR)/drive/iecieee/iecieee.c \
$(TOPDIR)/drive/iecieee/via2d.c

libdriveiecc64exp = \
$(TOPDIR)/drive/iec/c64exp/c64exp-cmdline-options.c \
$(TOPDIR)/drive/iec/c64exp/c64exp-resources.c \
$(TOPDIR)/drive/iec/c64exp/iec-c64exp.c \
$(TOPDIR)/drive/iec/c64exp/mc6821.c \
$(TOPDIR)/drive/iec/c64exp/profdos.c \

libdriveieee = \
$(TOPDIR)/drive/ieee/fdc.c \
$(TOPDIR)/drive/ieee/ieee-cmdline-options.c \
$(TOPDIR)/drive/ieee/ieee-resources.c \
$(TOPDIR)/drive/ieee/ieee.c \
$(TOPDIR)/drive/ieee/ieeerom.c \
$(TOPDIR)/drive/ieee/memieee.c \
$(TOPDIR)/drive/ieee/riot1d.c \
$(TOPDIR)/drive/ieee/riot2d.c \
$(TOPDIR)/drive/ieee/via1d2031.c \

libdrive = \
$(TOPDIR)/drive/drive-check.c \
$(TOPDIR)/drive/drive-cmdline-options.c \
$(TOPDIR)/drive/drive-overflow.c \
$(TOPDIR)/drive/drive-resources.c \
$(TOPDIR)/drive/drive-snapshot.c \
$(TOPDIR)/drive/drive-writeprotect.c \
$(TOPDIR)/drive/drive.c \
$(TOPDIR)/drive/drivecpu.c \
$(TOPDIR)/drive/drivemem.c \
$(TOPDIR)/drive/driveimage.c \
$(TOPDIR)/drive/driverom.c \
$(TOPDIR)/drive/drivesync.c \
$(TOPDIR)/drive/rotation.c \

libparallel = \
$(TOPDIR)/parallel/parallel-trap.c \
$(TOPDIR)/parallel/parallel.c \

libvdrive = \
$(TOPDIR)/vdrive/vdrive-bam.c \
$(TOPDIR)/vdrive/vdrive-command.c \
$(TOPDIR)/vdrive/vdrive-dir.c \
$(TOPDIR)/vdrive/vdrive-iec.c \
$(TOPDIR)/vdrive/vdrive-internal.c \
$(TOPDIR)/vdrive/vdrive-rel.c \
$(TOPDIR)/vdrive/vdrive-snapshot.c \
$(TOPDIR)/vdrive/vdrive.c \

libraster = \
$(TOPDIR)/raster/raster-cache.c \
$(TOPDIR)/raster/raster-canvas.c \
$(TOPDIR)/raster/raster-changes.c \
$(TOPDIR)/raster/raster-cmdline-options.c \
$(TOPDIR)/raster/raster-line-changes-sprite.c \
$(TOPDIR)/raster/raster-line-changes.c \
$(TOPDIR)/raster/raster-line.c \
$(TOPDIR)/raster/raster-modes.c \
$(TOPDIR)/raster/raster-resources.c \
$(TOPDIR)/raster/raster-sprite.c \
$(TOPDIR)/raster/raster-sprite-status.c \
$(TOPDIR)/raster/raster-sprite-cache.c \
$(TOPDIR)/raster/raster.c \

libsid = \
$(TOPDIR)/sid/fastsid.c \
$(TOPDIR)/sid/sid-cmdline-options.c \
$(TOPDIR)/sid/sid-resources.c \
$(TOPDIR)/sid/sid-snapshot.c \
$(TOPDIR)/sid/sid.c \

libsounddrv = \
$(TOPDIR)/sounddrv/soundaiff.c \
$(TOPDIR)/sounddrv/sounddummy.c \
$(TOPDIR)/sounddrv/sounddump.c \
$(TOPDIR)/sounddrv/soundfs.c \
$(TOPDIR)/sounddrv/soundiff.c \
$(TOPDIR)/sounddrv/soundspeed.c \
$(TOPDIR)/sounddrv/soundvoc.c \
$(TOPDIR)/sounddrv/soundwav.c

libgfxoutputdrv = \
$(TOPDIR)/gfxoutputdrv/bmpdrv.c \
$(TOPDIR)/gfxoutputdrv/gfxoutput.c \
$(TOPDIR)/gfxoutputdrv/iffdrv.c \
$(TOPDIR)/gfxoutputdrv/pcxdrv.c \
$(TOPDIR)/gfxoutputdrv/ppmdrv.c \

libprinterdrv = \
$(TOPDIR)/printerdrv/driver-select.c \
$(TOPDIR)/printerdrv/drv-ascii.c \
$(TOPDIR)/printerdrv/drv-mps803.c \
$(TOPDIR)/printerdrv/drv-nl10.c \
$(TOPDIR)/printerdrv/interface-serial.c \
$(TOPDIR)/printerdrv/interface-userport.c \
$(TOPDIR)/printerdrv/output-graphics.c \
$(TOPDIR)/printerdrv/output-select.c \
$(TOPDIR)/printerdrv/output-text.c \
$(TOPDIR)/printerdrv/printer-serial.c \
$(TOPDIR)/printerdrv/printer-userport.c \
$(TOPDIR)/printerdrv/printer.c \

librs232drv = \
$(TOPDIR)/rs232drv/rs232drv.c \
$(TOPDIR)/rs232drv/rsuser.c \

libvicii = \
$(TOPDIR)/vicii/vicii-badline.c \
$(TOPDIR)/vicii/vicii-clock-stretch.c \
$(TOPDIR)/vicii/vicii-cmdline-options.c \
$(TOPDIR)/vicii/vicii-color.c \
$(TOPDIR)/vicii/vicii-draw.c \
$(TOPDIR)/vicii/vicii-fetch.c \
$(TOPDIR)/vicii/vicii-irq.c \
$(TOPDIR)/vicii/vicii-mem.c \
$(TOPDIR)/vicii/vicii-phi1.c \
$(TOPDIR)/vicii/vicii-resources.c \
$(TOPDIR)/vicii/vicii-snapshot.c \
$(TOPDIR)/vicii/vicii-sprites.c \
$(TOPDIR)/vicii/vicii-timing.c \
$(TOPDIR)/vicii/vicii.c \

libvideo = \
$(TOPDIR)/video/render1x1.c \
$(TOPDIR)/video/render1x1pal.c \
$(TOPDIR)/video/render1x2.c \
$(TOPDIR)/video/render2x2.c \
$(TOPDIR)/video/render2x2pal.c \
$(TOPDIR)/video/renderscale2x.c \
$(TOPDIR)/video/renderyuv.c \
$(TOPDIR)/video/video-canvas.c \
$(TOPDIR)/video/video-cmdline-options.c \
$(TOPDIR)/video/video-color.c \
$(TOPDIR)/video/video-render-1x2.c \
$(TOPDIR)/video/video-render-2x2.c \
$(TOPDIR)/video/video-render-pal.c \
$(TOPDIR)/video/video-render.c \
$(TOPDIR)/video/video-resources-pal.c \
$(TOPDIR)/video/video-resources.c \
$(TOPDIR)/video/video-viewport.c \

libarch = \
$(TOPDIR)/arch/ps1/nugget/common/crt0/crt0.s \
$(TOPDIR)/arch/ps1/nugget/common/syscalls/printf.s \
$(TOPDIR)/arch/ps1/main.c \
\
$(TOPDIR)/arch/ps1/nugget/tests/uC-sdk-glue/BoardConsole.c \
$(TOPDIR)/arch/ps1/nugget/tests/uC-sdk-glue/BoardInit.c \
$(TOPDIR)/arch/ps1/nugget/tests/uC-sdk-glue/init.c \
\
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/libc/src/cxx-glue.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/libc/src/errno.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/libc/src/initfini.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/libc/src/malloc.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/libc/src/qsort.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/libc/src/rand.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/libc/src/reent.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/libc/src/stdio.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/libc/src/string.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/libc/src/strto.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/libc/src/unistd.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/libc/src/xprintf.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/libc/src/xscanf.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/libc/src/yscanf.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/os/src/devfs.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/os/src/filesystem.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/os/src/fio.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/os/src/hash-djb2.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/os/src/init.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/os/src/osdebug.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/os/src/romfs.c \
$(TOPDIR)/arch/ps1/nugget/third_party/uC-sdk/os/src/sbrk.c \

libmonitor = \
$(TOPDIR)/monitor/asm6502.c \
$(TOPDIR)/monitor/asmz80.c \
$(TOPDIR)/monitor/mon_assemble6502.c \
$(TOPDIR)/monitor/mon_assemblez80.c \
$(TOPDIR)/monitor/mon_breakpoint.c \
$(TOPDIR)/monitor/mon_command.c \
$(TOPDIR)/monitor/mon_disassemble.c \
$(TOPDIR)/monitor/mon_drive.c \
$(TOPDIR)/monitor/mon_file.c \
$(TOPDIR)/monitor/mon_memory.c \
$(TOPDIR)/monitor/mon_register6502.c \
$(TOPDIR)/monitor/mon_registerz80.c \
$(TOPDIR)/monitor/mon_ui.c \
$(TOPDIR)/monitor/mon_util.c \
$(TOPDIR)/monitor/monitor.c \

libdiskimage = \
$(TOPDIR)/diskimage/diskimage.c \
$(TOPDIR)/diskimage/fsimage-check.c \
$(TOPDIR)/diskimage/fsimage-create.c \
$(TOPDIR)/diskimage/fsimage-gcr.c \
$(TOPDIR)/diskimage/fsimage-probe.c \
$(TOPDIR)/diskimage/fsimage.c \

libiecbus = \
$(TOPDIR)/iecbus/iecbus.c \

libserial= \
$(TOPDIR)/serial/fsdrive.c \
$(TOPDIR)/serial/serial-device.c \
$(TOPDIR)/serial/serial-iec-bus.c \
$(TOPDIR)/serial/serial-iec-device.c \
$(TOPDIR)/serial/serial-iec-lib.c \
$(TOPDIR)/serial/serial-iec.c \
$(TOPDIR)/serial/serial-realdevice.c \
$(TOPDIR)/serial/serial-trap.c \
$(TOPDIR)/serial/serial.c \

libfsdevice = \
$(TOPDIR)/fsdevice/fsdevice-close.c \
$(TOPDIR)/fsdevice/fsdevice-cmdline-options.c \
$(TOPDIR)/fsdevice/fsdevice-flush.c \
$(TOPDIR)/fsdevice/fsdevice-open.c \
$(TOPDIR)/fsdevice/fsdevice-read.c \
$(TOPDIR)/fsdevice/fsdevice-resources.c \
$(TOPDIR)/fsdevice/fsdevice-write.c \
$(TOPDIR)/fsdevice/fsdevice.c \

libtape = \
$(TOPDIR)/tape/t64.c \
$(TOPDIR)/tape/tap.c \
$(TOPDIR)/tape/tape-internal.c \
$(TOPDIR)/tape/tape-snapshot.c \
$(TOPDIR)/tape/tape.c \
$(TOPDIR)/tape/tapeimage.c \

libimagecontents = \
$(TOPDIR)/imagecontents/diskcontents-block.c \
$(TOPDIR)/imagecontents/diskcontents-iec.c \
$(TOPDIR)/imagecontents/diskcontents.c \
$(TOPDIR)/imagecontents/imagecontents.c \
$(TOPDIR)/imagecontents/tapecontents.c \

libfileio = \
$(TOPDIR)/fileio/cbmfile.c \
$(TOPDIR)/fileio/fileio.c \
$(TOPDIR)/fileio/p00.c \

libcore = \
$(TOPDIR)/core/ciacore.c \
$(TOPDIR)/core/ciatimer.c \
$(TOPDIR)/core/riotcore.c \
$(TOPDIR)/core/tpicore.c \
$(TOPDIR)/core/viacore.c \

base_sources = \
$(TOPDIR)/alarm.c \
$(TOPDIR)/attach.c \
$(TOPDIR)/autostart.c \
$(TOPDIR)/charset.c \
$(TOPDIR)/clkguard.c \
$(TOPDIR)/clipboard.c \
$(TOPDIR)/cmdline.c \
$(TOPDIR)/cbmdos.c \
$(TOPDIR)/cbmimage.c \
$(TOPDIR)/color.c \
$(TOPDIR)/crc32.c \
$(TOPDIR)/debug.c \
$(TOPDIR)/dma.c \
$(TOPDIR)/emuid.c \
$(TOPDIR)/event.c \
$(TOPDIR)/findpath.c \
$(TOPDIR)/fliplist.c \
$(TOPDIR)/gcr.c \
$(TOPDIR)/info.c \
$(TOPDIR)/init.c \
$(TOPDIR)/initcmdline.c \
$(TOPDIR)/interrupt.c \
$(TOPDIR)/joystick.c \
$(TOPDIR)/kbdbuf.c \
$(TOPDIR)/keyboard.c \
$(TOPDIR)/lib.c \
$(TOPDIR)/log.c \
$(TOPDIR)/machine-bus.c \
$(TOPDIR)/machine.c \
$(TOPDIR)/main.c \
$(TOPDIR)/mouse.c \
$(TOPDIR)/network.c \
$(TOPDIR)/palette.c \
$(TOPDIR)/ram.c \
$(TOPDIR)/rawfile.c \
$(TOPDIR)/resources.c \
$(TOPDIR)/romset.c \
$(TOPDIR)/screenshot.c \
$(TOPDIR)/snapshot.c \
$(TOPDIR)/sound.c \
$(TOPDIR)/sysfile.c \
$(TOPDIR)/translate.c \
$(TOPDIR)/traps.c \
$(TOPDIR)/util.c \
$(TOPDIR)/zfile.c \
$(TOPDIR)/zipcode.c \

maincpu_sources = \
$(TOPDIR)/maincpu.c \

SRCS = \
$(libc64) \
$(libc64cart) \
$(libdriveiec) \
$(libdriveiecieee) \
$(libdriveiecc64exp) \
$(libdriveieee) \
$(libdrive) \
$(libparallel) \
$(libvdrive) \
$(libraster) \
$(libsid) \
$(libsounddrv) \
$(libgfxoutputdrv) \
$(libprinterdrv) \
$(librs232drv) \
$(libvicii) \
$(libvideo) \
$(libarch) \
$(libmonitor) \
$(libdiskimage) \
$(libiecbus) \
$(libserial) \
$(libfsdevice) \
$(libtape) \
$(libimagecontents) \
$(libfileio) \
$(libcore) \
$(base_sources) \
$(maincpu_sources) \

include $(TOPDIR)/arch/ps1/nugget/common.mk
