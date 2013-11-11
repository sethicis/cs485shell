/* This file is holds all the global variables and information needed for the modules in this program to work.
Created by: Kyle
Date: 11/8/2013
Last Edit by: Libby
Edit Date: 11/10/2013 */


#define MAXBUFF         256 /* Maximum buffer size for value string */
#define TYPEBUFF        20  /* Maximum buffer size for type strings */

/* Our token "object" that will be passed around */
/*@param val: the actual contents of the token (eg. filepath) 
  @param type: the token type (WORD, STRING, METACHAR, EOL)
  @param next: pointer to next token in sequence */
typedef struct{
    char* val;
    char* type;
    struct token* next;
}token;


int scan(void);         /* Scans stdin */
token* newToken(void);  /* Generates a new token */
