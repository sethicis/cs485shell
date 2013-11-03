#Makefile for CS485 project 3
#Created by Libby and Kyle
GCC = gcc -Wall -pedantic
OBJECTS = lex.yy.o main.o
HEADERS = global.h

ioShell: $(OBJECTS)
	$(GCC) $(OBJECTS) -o ioShell

lex.yy.o: lex.yy.c $(HEADERS)
	$(GCC) -c lex.yy.c

lex.yy.c: scanner.l
	flex scanner.l

main.o: global.h main.c
	$(GCC) -c main.c

clean:
	-rm -f $(OBJECTS) ioShell