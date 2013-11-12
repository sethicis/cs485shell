cs485shell
==========

Created by: Libby and Kyle
Project born: 11-03-13

This is a cs485 project where the objective is to create a UNIX shell

Kyle will manage the scanner module; Libby will manage the parser.

Recent changes:
=========
(11-11-13):
* Added new functions to tokenGen.c, completely rewrote stripper.c.
* Stripper.c does a lot less stripping and a lot more analyzing now.
* The major function in stripper.c is linkToken() which handles inserting
new tokens into to the linked list of tokens.
* Modified main.c to initialize fTok on launch, and be usable as official entry point for program.
* Added tons of new comments to all files used.
* Added a new test file call pTest which pretends to be the parser
function, so the scanner and token linked list can be tested.
* Updated global.h with new declarations
* Added stripper.c, tokenGen.c, and pTest.c to makefile.
----
(Old Changes)
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
scanner.l calls stripper.c's linkToken() to insert identified tokens.
stripper.c: Calls newToken() and assignTok() in tokenGen.c to generate and
populate tokens.
tokenGen.c: Creates new dynamically allocated tokens.
 
Parser:
==========
