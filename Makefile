CC=gcc
CFLAGS=--std=c17 -Wall -Werror -Wextra -pedantic \
		-Isrc/ -ggdb -DDEBUG
BUILDDIR=build
SRCDIR=src

all: $(BUILDDIR)/mem.o $(BUILDDIR)/utils.o $(BUILDDIR)/main.o
	$(CC) -o $(BUILDDIR)/main $^

build:
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/mem.o: $(SRCDIR)/mem.c build
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/mem_debug.o: $(SRCDIR)/mem_debug.c build
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/utils.o: $(SRCDIR)/utils.c build
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/main.o: $(SRCDIR)/main.c build
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILDDIR)

