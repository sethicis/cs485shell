/* This file is the lexical analyzer / scanner for CS485 Project 3 Unix Shell */
/* As designed by Kyle and Libby */
/* The tokenized values found in this program are passed to the parser for further evaluation */
%{
/* Includes */
#include "global.h" /* Contains the list of globals */
#include <stdio.h> /* Used for io operations */
%}

/******* Definitions *******/
delim   [\t ]
ws      {delim}+
alpha   [a-zA-Z]
path    [a-zA-Z//]
db      (debug){delim}+
cd      (chdir){ws}{path}+
EOL     (\n)
word    {path}+
string  (\".+\")
meta    [<>#]

/******* Rules ********/
%%
{ws}				{/*Do nothing*/}
{word}              {printf("Saw a word: %s\n",yytext);}
{string}            {printf("Saw a string: %s\n",yytext);}
<<EOF>>             {printf("Saw an EOF\n");return 0;}
.                   {/*Do nothing*/}
%%
/******* User Code ******/
int yywrap(void){return 1;}

int scan(void){
	yyin = stdin;
	return yylex();
}