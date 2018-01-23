# SPDX-License-Identifier: MIT
# Copyright (c) 2017 Andrea Loi
# Copyright (c) 2018 Aleksey Makarov

CROSS_COMPILE = arm-none-eabi-

CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy
SIZE    = $(CROSS_COMPILE)size
GDB     = $(CROSS_COMPILE)gdb
AR      = $(CROSS_COMPILE)ar

MCPU = -mcpu=cortex-m3 -mthumb -mabi=aapcs

CFLAGS  = $(MCPU) -O0 -ggdb -ffreestanding -Wall -Wextra -I./libbsd
LDFLAGS = $(MCPU)     -ggdb -static -nostdlib -TSTM32F103C8.ld -L.
LDLIBS  = -lgcc -lstm

# tests (programs)
ELFS = test01_uart_putc test02_uart_inout test03_stdio test04_i2c test05_blink test06_dwt
BINS = $(addsuffix .bin, $(ELFS))

.PHONY: all clean

all: $(BINS)

include ./libbsd/Makefile.libbsd
LIBBSD_OBJS_P=$(addprefix ./libbsd/, $(LIBBSD_OBJS))

# functions that may be shared between tests
libstm.a: $(LIBBSD_OBJS_P) init.o rcc.o gpio.o uart.o dwt.o i2c.o
	$(AR) rcs $@ $^

$(ELFS) : libstm.a

%.bin: %
	$(OBJCOPY) -O binary $< $@

%.lst: %
	$(OBJDUMP) -x -S $< > $@

%.dis: %
	$(OBJDUMP) -D $< > $@

%.size: %
	$(SIZE) $< > $@

clean:
	$(RM) -f *.o *.a *.bin *.size *.dis *.lst $(ELFS) ./libbsd/*.o
