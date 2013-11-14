/* This file is holds all the global variables and information needed for the modules in this program to work.
Created by: Kyle
Date: 11/8/2013
Last Edit by: Libby
Edit Date: 11/10/2013 */

/* global.h */

/* This module holds all the global variables and information needed for the
 other modules in the program to communicate with each other. */
/* Create for CS485 Project 3 */
/* Authors: Libby and Kyle */


/* NOTE: The Buffer defines may not be needed anymore */
#define MAXBUFF         256 /* Maximum buffer size for value string */
#define TYPEBUFF        20  /* Maximum buffer size for type strings */
#define TWORD           "word\0"
#define TSTRING         "string\0"
#define TMETA           "metachar\0"
#define TEOL            "end-of-line\0"

char* cPrompt;  /* The prompt for the ioShell program */

/* Our token "object" that will be passed around */
typedef struct token token;
/* Defines the enum set for token usage */
typedef enum{
    NIL = 0,
    COMMENT = 1,
    SPROMPT = 2,
    DEBUG = 3,
    CD = 4,
    BIN = 5,
    META = 6,
    QUIT = 7,
    STRING = 8,
    ARG = 9
} tUsage;
struct token{
/*@param val: the actual contents of the token (eg. filepath) 
  @param type: the token type (WORD, STRING, METACHAR, EOL)
  @param next: pointer to next token in sequence */
    char* val;
    char* type;
    token* next; /* Pointer to next token */
    token* prev; /* Pointer to previous token */
    tUsage usage; /* Usage of token */
};

token* fTok; /* Global pointer to the first token in the linked list */

void chPrompt(char*);   /* Simple helper function that sets the terminal prompt */
int scan(void);         /* Scans stdin */
token* newToken(void);  /* Generates a new token */
token* linkTok(token*,char*,char*);   /* Inserts token into linked list */
void assignTok(token*,char*,char*);   /* Assigns the value and type to the given token */
void parse(void);                  /* Parse the linked list of tokens */
void stripOut(char*);              /* Removes the quotes from string type tokens */

