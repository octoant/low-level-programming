.PHONY: all clean

ASM=nasm
ASMFLAGS=-felf64 -g
CC=gcc
CFLAGS=-Iinclude/ -std=c17 -pedantic -Wall -Werror -ggdb -c
LINKER=$(CC)
LDFLAGS=-no-pie -g

BUILDDIR=build
SRCDIR=src

MKDIR=mkdir -p
RM=rm -rf

all: $(BUILDDIR)
	$(ASM) $(ASMFLAGS) -o $(BUILDDIR)/sepia.asm.o $(SRCDIR)/sepia.asm

	$(CC) $(CFLAGS) -o $(BUILDDIR)/dimensions.o $(SRCDIR)/dimensions.c
	$(CC) $(CFLAGS) -o $(BUILDDIR)/image.o 		$(SRCDIR)/image.c
	$(CC) $(CFLAGS) -o $(BUILDDIR)/file.o 		$(SRCDIR)/file.c
	$(CC) $(CFLAGS) -o $(BUILDDIR)/sepia.o 		$(SRCDIR)/sepia.c
	$(CC) $(CFLAGS) -o $(BUILDDIR)/transform.o 	$(SRCDIR)/transform.c
	$(CC) $(CFLAGS) -o $(BUILDDIR)/bmp.o 		$(SRCDIR)/bmp.c
	$(CC) $(CFLAGS) -o $(BUILDDIR)/utils.o 		$(SRCDIR)/utils.c
	$(CC) $(CFLAGS) -o $(BUILDDIR)/main.o 		$(SRCDIR)/main.c

	$(LINKER) $(LDFLAGS) -o $(BUILDDIR)/sepia-filter $(BUILDDIR)/*.o

$(BUILDDIR):
	$(MKDIR) $@

clean:
	$(RM) $(BUILDDIR)
