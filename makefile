#Makefile for CS485 project 3
#Created by Libby and Kyle
GCC = gcc -Wall -pedantic
OBJECTS = lex.yy.o main.o stripper.o tokenGen.o actions.o
HEADERS = global.h

ioShell: $(OBJECTS) pTest.o
	$(GCC) $(OBJECTS) pTest.o -o ioShell

lex.yy.o: $(HEADERS) lex.yy.c
	$(GCC) -c lex.yy.c

lex.yy.c: scanner.l
	flex scanner.l

main.o: $(HEADERS) main.c
	$(GCC) -c main.c

stripper.o: $(HEADERS) stripper.c
	$(GCC) -c stripper.c

tokenGen.o: $(HEADERS) tokenGen.c
	$(GCC) -c tokenGen.c

actions.o: $(HEADERS) actions.c
	$(GCC) -c actions.c

pTest.o: $(HEADERS) pTest.c
	$(GCC) -c pTest.c

clean:
	-rm -f *.o lex.yy.c ioShell
