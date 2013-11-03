/* This file is the lexical analyzer / scanner for CS485 Project 3 Unix Shell */
/* As designed by Kyle and Libby */
/* The tokenized values found in this program are passed to the parser for further evaluation */
%{
/* Includes */
#include "global.h" /* Contains the list of globals */
#include <stdio.h> /* Used for io operations */
%}

/******* Definitions *******/
delim	[\t ]
ws		{delim}+
alpha	[a-zA-Z]
path	[{alpha}/]
db		(debug){delim}+
cd		(chdir){ws}{path}+

/******* Rules ********/
%%
{ws}						{/*Do nothing*/}
"setprompt"{ws}{alpha}+		{printf("saw pset\n");}
{db}"on"					{printf("Turning Debug ON\n");}
{db}"off"				{printf("Turning Debug OFF\n");}
{cd}			{printf("Saw a CD command\n");}
"quit"			{printf("I QUIT!!!\n"); return 0;}		/* Terminates the program */
<<EOF>>			{printf("Saw an EOF\n");return 0;}
.				{/*Do nothing*/}
%%
/******* User Code ******/
int yywrap(void){return 1;}

int scan(void){
	yyin = stdin;
	return yylex();
}