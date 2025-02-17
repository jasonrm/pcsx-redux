BOOT ?= rom

TARGET = openbios
TYPE = bin

SRCS = \
../common/hardware/sio1.c \
../common/psxlibc/fastmemset.s \
boot/boot.s \
card/backupunit.c \
card/device.c \
cdrom/cdrom.c \
cdrom/events.c \
cdrom/filesystem.c \
cdrom/helpers.c \
cdrom/statemachine.c \
charset/sjis.c \
fileio/filesystem.c \
fileio/misc.c \
fileio/stdio.c \
gpu/gpu.c \
handlers/irq.c \
handlers/setup.c \
handlers/syscall.c \
kernel/alloc.c \
kernel/events.c \
kernel/flushcache.s \
kernel/handlers.c \
kernel/libcmisc.c \
kernel/misc.c \
kernel/psxexe.c \
kernel/psxexec.s \
kernel/setjmp.s \
kernel/threads.c \
kernel/util.c \
kernel/vectors.s \
main/main.c \
pio/pio.c \
shell/shell.c \
sio0/busyloop.s \
sio0/card.c \
sio0/cardfasttrack.s \
sio0/driver.c \
sio0/pad.c \
tty/tty.c \
\
patches/hash.c \
patches/patches.c \
\
patches/clear_card_1.c \
patches/initgun_1.c \
patches/patch_card_info_1.c \
patches/patch_card_1.c \
patches/patch_card_2.c \
patches/patch_card2_1.c \
patches/patch_card2_2.c \
patches/patch_gte_1.c \
patches/patch_gte_2.c \
patches/patch_gte_3.c \
patches/patch_pad_1.c \
patches/patch_pad_2.c \
patches/patch_pad_3.c \
patches/remove_ChgclrPAD_1.c \
patches/remove_ChgclrPAD_2.c \
patches/send_pad_1.c \
patches/send_pad_2.c \
\
../shell/shell_data.o \
\
uC-sdk-glue/BoardConsole.c \
uC-sdk-glue/BoardInit.c \
uC-sdk-glue/init.c \
\
../../../third_party/uC-sdk/libc/src/errno.c \
../../../third_party/uC-sdk/libc/src/initfini.c \
../../../third_party/uC-sdk/libc/src/qsort.c \
../../../third_party/uC-sdk/libc/src/rand.c \
../../../third_party/uC-sdk/libc/src/reent.c \
../../../third_party/uC-sdk/libc/src/string.c \
../../../third_party/uC-sdk/libc/src/strto.c \
../../../third_party/uC-sdk/libc/src/xprintf.c \
../../../third_party/uC-sdk/libc/src/xscanf.c \
../../../third_party/uC-sdk/libc/src/yscanf.c \
../../../third_party/uC-sdk/os/src/init.c \
../../../third_party/uC-sdk/os/src/osdebug.c \

ifeq ($(BOOT),rom)
LDSCRIPT = psx-bios.ld
SRCS += font1.o font2.o
else
LDSCRIPT = psx-bios-as-cart.ld
endif

CPPFLAGS = -DNOFLOATINGPOINT -DXPRINTFNOALLOC -DXPRINTFNOSTDIO
CPPFLAGS += -I../../../third_party/uC-sdk/libc/include
CPPFLAGS += -I../../../third_party/uC-sdk/os/include
CPPFLAGS += -IuC-sdk-glue

ifneq ($(EMBED_PSEXE),)
CPPFLAGS += -DOPENBIOS_USE_EMBEDDED_PSEXE
SRCS += ./psexe_data.o
endif

ifneq ($(FASTBOOT),)
CPPFLAGS += -DOPENBIOS_FASTBOOT
endif

ifneq ($(INSTALL_TTY_CONSOLE),)
CPPFLAGS += -DOPENBIOS_INSTALL_TTY_CONSOLE
endif

include ../common.mk

../shell/shell_data.o: shell

./psexe_data.o: $(EMBED_PSEXE)
	cp $(EMBED_PSEXE) psexe.bin
	$(PREFIX)-objcopy -I binary --rename-section .data=.rodata,alloc,load,readonly,data,contents -O $(FORMAT) -B mips psexe.bin psexe_data.o

./font1.o: charset/font1.raw
	$(PREFIX)-objcopy -I binary --rename-section .data=.font1,alloc,load,readonly,data,contents -O $(FORMAT) -B mips charset/font1.raw font1.o

./font2.o: charset/font2.raw
	$(PREFIX)-objcopy -I binary --rename-section .data=.font2,alloc,load,readonly,data,contents -O $(FORMAT) -B mips charset/font2.raw font2.o

shell:
	$(MAKE) -C ../shell shell_data.o

deepclean: clean
	$(MAKE) -C ../shell clean

.PHONY: deepclean shell
