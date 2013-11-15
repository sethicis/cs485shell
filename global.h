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
#define TEOL		"end-of-line\0"
#define SEOL		"single-eol\0"
#define USETPROMPT	"setprompt\0"
#define UPOUND		"#\0"
#define UCHDIR		"chdir\0"
#define UDEBUG		"debug\0"
#define UOFF		"off\0"
#define UON		"on\0"
#define UQUIT		"quit\0"
#define LTHAN   "<\0"
#define GTHAN   ">\0"

char* cPrompt;  /* The prompt for the ioShell program */
int debugFlag; /* Global variable for the debug command */
char* wkDir; /* Global variable for the current working directory */
int errFlag; /* Global variable used to flag code errors */
int empty;
/* Our token "object" that will be passed around */
typedef struct token token;
/* Defines the enum set for token usage */
typedef enum{
    NIL,
    COMMENT,
    SPROMPT,
    DEBUG,
    CD,
    CMD,
    IFILE,
    OFILE,
    META,
    QUIT,
    STRING,
    ARG,
    WORD,
    EOL
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
token* lTok; /* Global pointer to the last token in the linked list */

void debug(void);  /* Traverses the linked list and prints the attributes of every token*/
void chPrompt(char*);   /* Simple helper function that sets the terminal prompt */
int scan(void);         /* Scans stdin */
token* newToken(void);  /* Generates a new token */
token* linkTok(token*,char*,char*);   /* Inserts token into linked list */
void assignTok(token*,char*,char*);   /* Assigns the value and type to the given token */
void parse(void);                  /* Parse the linked list of tokens */
void stripOut(char*);              /* Removes the quotes from string type tokens */
void handleCmd(void);               /* Prepares token values for execution */
void exCmd(char**,char*,char*);     /* Creates child process are starts program */
void cleanup(void);                /* Destroy unneeded tokens */
void locate(void);                  /* Determines what the current working directory */
void decide(void);                   /* Determines which actions to take on the parsed tokens */
void terminate(void);               /* Used to gracefully shutdown the shell */
