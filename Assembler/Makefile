all: assembler asm_parser

asm_parser.o: asm_parser.c asm_parser.h
	clang -c -g asm_parser.c

asm_parser: asm_parser.o
	clang -c -g asm_parser.c -o asm_parser

assembler.o: assembler.c
	clang -c -g assembler.c

assembler: assembler.o asm_parser.o
	clang -g asm_parser.c assembler.o -o assembler

clean:
	rm -rf *.o

clobber: clean
	rm -rf assembler asm_parser