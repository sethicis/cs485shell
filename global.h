<<<<<<< .merge_file_aGrjS4
=======
/* This file is holds all the global variables and information needed for the modules in this program to work.
Created by: Kyle
Date: 11/8/2013
Last Edit by: Libby
Edit Date: 11/10/2013 */
>>>>>>> .merge_file_45E4lD

/* global.h */

/* This module holds all the global variables and information needed for the
 other modules in the program to communicate with each other. */
/* Create for CS485 Project 3 */
/* Authors: Libby and Kyle */


/* NOTE: The Buffer defines may not be needed anymore */
#define MAXBUFF         256 /* Maximum buffer size for value string */
#define TYPEBUFF        20  /* Maximum buffer size for type strings */
/*const char* TWORD = "WORD";
const char* TSTRING = "STRING";
const char* TMETA = "META";
const char* TEOL = "\n";*/
#define TWORD           "word\0"
#define TSTRING         "string\0"
#define TMETA           "metachar\0"
#define TEOL            "end-of-line\0"

/* Our token "object" that will be passed around */
<<<<<<< .merge_file_aGrjS4
typedef struct token token;
struct token{
=======
/*@param val: the actual contents of the token (eg. filepath) 
  @param type: the token type (WORD, STRING, METACHAR, EOL)
  @param next: pointer to next token in sequence */
typedef struct{
>>>>>>> .merge_file_45E4lD
    char* val;
    char* type;
    token* next; /* Pointer to next token */
    token* prev; /* Pointer to previous token */
};
token* fTok; /* Global pointer to the first token in the linked list */

int scan(void);         /* Scans stdin */
token* newToken(void);  /* Generates a new token */<<<<<<< .merge_file_aGrjS4
token* linkTok(token*,char*,char*);   /* Inserts token into linked list */
void assignTok(token*,char*,char*);   /* Assigns the value and type to the given token */
void parse(void);                  /* Parse the linked list of tokens */
void stripOut(char*);              /* Removes the quotes from string type tokens */
=======
>>>>>>> .merge_file_45E4lD
