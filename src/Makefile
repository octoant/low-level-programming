ASM=nasm
ASMFLAGS=-f elf64
LD=ld

all: dictionary

dictionary: main.o dict.o lib.o
	$(LD) -o $@ $^

main.o: main.asm dict.o lib.o *.inc
	$(ASM) $(ASMFLAGS) -o $@ $<

dict.o: dist.asm lib.o lib.inc
	$(ASM) $(ASMFLAGS) -o $@ $<

lib.o: lib.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

clean:
	rm -f *.o dictionary

.PHONY: clean
