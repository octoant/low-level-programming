ASM=nasm
ASMFLAGS=-f elf64
LD=ld

all: dictionary

dictionary: main.o dict.o lib.o
	$(LD) -o $@ $^

main.o: main.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

dict.o: dist.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

lib.o: lib.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

clean:
	rm -f *.o dictionary

.PHONY: clean
