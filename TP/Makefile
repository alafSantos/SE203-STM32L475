PREFIX=arm-none-eabi-
CC    = $(PREFIX)gcc
AS    = $(PREFIX)as
LD    = $(PREFIX)ld
GDB   = $(PREFIX)gdb
OBJCOPY  = $(PREFIX)objcopy

FPU = -mfloat-abi=hard -mfpu=fpv4-sp-d16
TARGET_ARCH = -mcpu=cortex-m4 -mthumb $(FPU)
CLK = clocks.o
LDFLAGS = -T ld_ram.lds -nostdlib
ASFLAGS = -g
DUMPFLAGS = -d
EXE  = main
OBJS = main.o crt0.o init.o memfuncs.o led.o uart.o matrix.o image.o irq.o buttons.o

CMSISDIR1 = CMSIS/Device/ST/STM32L4xx/Include
CMSISDIR2 = CMSIS/Include
INCLUDEPATH = $(CMSISDIR1) $(CMSISDIR2)
WARNINGS = -Wall -Werror -Wextra
CFLAGS  = -c -g -O1 -ffreestanding $(WARNINGS) $(addprefix -I ,${INCLUDEPATH})

.PHONY: connect debug clean all # indique que la cible n'est pas un fichier, et qu'elle doit toujours être reconstruite

all: $(EXE)

$(EXE):$(OBJS) $(CLK)
	 $(LD) $(LDFLAGS) $^ -o $@

image.o : image.raw
	$(OBJCOPY) -I binary -O elf32-littlearm -B arm image.raw image.o

connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug: $(EXE)
	$(GDB) -x se203.gdb $(EXE)

clean:
	rm -f $(OBJS) $(EXE)
