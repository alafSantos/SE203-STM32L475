PREFIX=arm-none-eabi-
CC    = $(PREFIX)gcc
AS    = $(PREFIX)as
LD    = $(PREFIX)ld
GDB   = $(PREFIX)gdb

CFLAGS  = -c -g -O1 -Wall -Werror -Wextra -ffreestanding
TARGET_ARCH = -mcpu=cortex-m4 -mthumb
LDFLAGS = -T ld_ram.lds -nostdlib
ASFLAGS = -g
DUMPFLAGS = -d
EXE  = main
OBJS = main.o fibonacci.o crt0.o init.o memfuncs.o

.PHONY: connect debug clean all

all: $(EXE)

$(EXE):$(OBJS)
	 $(LD) $(LDFLAGS) $^ -o $@

connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug: $(EXE)
	$(GDB) -x se203.gdb $(EXE)

clean:
	rm -f $(OBJS) $(EXE)
