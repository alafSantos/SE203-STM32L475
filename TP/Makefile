PREFIX=arm-none-eabi-
GDB   = $(PREFIX)gdb

.PHONY: connect debug

connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug:
	$(GDB) -x se203.gdb
