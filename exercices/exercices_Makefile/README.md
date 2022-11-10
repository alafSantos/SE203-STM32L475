# Outils, langages et pratique des systèmes à microprocesseurs (partie I) - SE203

## Alaf do Nascimento Santos

**GNU Make et Makefiles**


```
CC=arm-none-eabi-gcc
CFLAGS = -Wall -Werror -g -Og
stubs.o: CFLAGS = -g -O2 # Le CFLAGS pour stubs.o va être different par rapport les autres
TARGET_ARCH = -mthumb
LDLIBS = -lm # pour la bibliothèque math.h
LDFLAGS = -L/opt/mylibs
VPATH = libs # pour trouver le stubs.c dans le dossier libs
CFILES  = $(wildcard *.c) # pour lister l'ensemble des fichiers qui portent l'extension .c
OBJS = $(CFILES:.c=.o) stubs.o # include *.o files
EXE = hello # executable name

.PHONY: all clean

all: $(EXE)

# produire un exécutable à partir de n fichiers C
$(EXE): $(OBJS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

# Nettoyage
clean:
	rm -f $(OBJS) $(EXE)
```