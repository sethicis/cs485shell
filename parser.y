%{
#include <stdio.h>
#include <stdlb.h>

/*flex functions for bison*/
extern int yylex();
extern int yyparse(); 

/*error handling*/
void yyerror(const char *s);

%}

/****types of tokens****/
%union {
	char *strval;
	char chval;
}


/*******Tokens*******/

/*****constant strings*****/
%token SETPROMPT "setprompt"
%token DEBUG "debug"
%token CHDIR "chdir"
%token QUIT "quit"
%token EOL EOL  /*check this*/
%token POUND "#"
%token LTHAN "<"
%token GTHAN ">"
%token ON "on"
%token OFF "off"

/****terminal tokens*****/

%token <strval> STRING
%token <strval> WORD

%%

line	: changeprompt		{printf("Setting prompt to %s\n", $2);}
	| exit			{printf("So long!");}
	| comment		{;}
	| debug_on		{printf("Turning debugging on");}
	| debug_off		{printf("Turning debugging off");}
	| changecurrent		{printf("Changing to directory %s\n", $2);}
	| execthis		{printf("Executing %s\n", $1);}
	| ioexec		{;}
	;

changeprompt	:	SETPROMPT STRING EOL
		;

exit		:	QUIT EOL
		;

comment		:	POUND EOL
		;

debug_on	:	DEBUG ON
		;

debug_off	:	DEBUG OFF
		;

changecurrent	:	changedir directory_name
		; 

execthis	:	command args
		|	command
		;

ioexec		:	command args metachar arg
		|	arg metachar command metachar arg
		|	arg metachar command
		;

changedir	:	CHDIR
		;

directory_name	:	WORD
		;

command		:	WORD
		;

args		:	args arg
		|	arg
		;

arg		:	WORD
		|	STRING
		;

metachar	:	LTHAN
		|	GTHAN
		;		

%%	

void yyerror(const char *s) {
  printf("Parse error detected with message: %s\n", s);
}

	
