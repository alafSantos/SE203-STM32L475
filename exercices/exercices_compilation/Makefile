PREFIX=arm-none-eabi-
AS    = $(PREFIX)as
LD    = $(PREFIX)ld
GDB   = $(PREFIX)gdb
ASFLAGS = -g
LDFLAGS = -g -Ttext 0x20000000

ASFILES  = $(wildcard *.s)
OBJFILES  = $(wildcard *.o)
ELFFILES = $(patsubst %.s,%.elf,$(ASFILES))
EXE = ex3

.PHONY: all clean run

all: $(EXE)
run: 
	@./$(EXE)

clean:
	rm -f $(ELFFILES) $(OBJFILES) $(EXE)
