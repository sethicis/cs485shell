/* This file is holds all the global variables and information needed for the modules in this program to work. */


#define MAXBUFF         256 /* Maximum buffer size for value string */
#define TYPEBUFF        20  /* Maximum buffer size for type strings */

/* Our token "object" that will be passed around */
typedef struct{
    char* val;
    char* type;
    struct token* next;
}token;


int scan(void);         /* Scans stdin */
token* newToken(void);  /* Generates a new token */