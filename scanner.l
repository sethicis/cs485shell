/* 
 scanner.l
 
 This file is the lexical analyzer / scanner for CS485 Project 3 Unix Shell */
/* As designed by Kyle and Libby */
/* This module handles the lexical analysis part of the Unix Shell. (Scanner) */
/* The tokenized values found in this program are passed to the parser for further evaluation */
%{
/******* Includes **********/
#include "global.h" /* Contains the list of globals */
#include <stdio.h> /* Used for io operations */
token* cTok;  /* Current token initially points to the fTok */
%}

/******* Definitions *******/
delim   [\t ]
ws      {delim}+
path    [0-9a-zA-Z//]
EOL     (\n)
word    {path}+
string  (\".+\")
meta    [<>#]

/******* Rules ********/
%%
{ws}            {/*Do nothing*/}
{word}          {cTok = linkTok(cTok,TWORD,yytext);}
{string}        {cTok = linkTok(cTok,TSTRING,yytext);}
{meta}          {cTok = linkTok(cTok,TMETA,yytext);}
{EOL}           {cTok = linkTok(cTok,TEOL,yytext); if (cTok != fTok) return 0;}
<<EOF>>         {return -1;}
.               {/*Do nothing*/}
%%
/******* User Code ******/
int yywrap(void){return 1;} /* Added so Flex won't yell about not being linked to yywrap */

/* This function is the driver for the Flex lexical analyzer */
int scan(void){
    cTok = fTok; /* Set the current token to the first token in the linked list */
	yyin = stdin;   /* Tell Flex to expect input from standard in */
	return yylex(); /* Call Flex generated function and return its result to the caller */
}