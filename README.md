cs485shell
==========

Created by: Libby and Kyle
Project born: 11-03-13

This is a cs485 project where the objective is to create a UNIX shell

Kyle will manage the scanner module; Libby will manage the parser.

Recent changes:
=========
Added a scanner.l, makefile, main.c, and global.h file to the git repository.
Scanner.l is the flex based lexcial analyzer.
Main.c is the test entry point for the program
Global.h is the organization base for the program that handles defines and structs.
The makefile is self explainitory.
==========

Scanner:
==========
Scanner.l works as the simple tokenizer / lexical analyzer.
Scanner.l is written using flex, so it should be easy to grab input strings
and files.  The basic structure of the scanner file looks for expected tokens, performs some initial cleanup on the input and then passes the token to the parser
for further evaluation.

Parser:
==========
