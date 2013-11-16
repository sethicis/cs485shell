/*
 stripper.c
 
  Created by Kyle Blagg on 11/8/13.
 This module contains the linking function for inserting tokens into
 the linked list and the stripOut function used to remove the quotes
 from STRING type tokens.

*/

#include <stdio.h>      /* Used for i/o and some string operations */
#include <string.h>     /* Used for string operations */
#include "global.h"     /* Used for global defines */

/* 
 NOTE: If token pointer does not change calling function values change function
 to return token* */
token* linkTok(token* tok, char* TYPE,char* value){
        /* Case: token type WORD */
    if (strcmp(TYPE,TWORD) == 0){
        assignTok(tok,value,TYPE); /* Assign the token values */
            /* Create a new token, set it's previous pointer to the current token,
             then set the current token's next pointer to the new token. */
        token* tmpTok; tmpTok = newToken();
        tmpTok->prev = tok;
        tok->next = tmpTok;
        return tmpTok;
    }
        /* Case: token type STRING */
    else if (strcmp(TYPE,TSTRING) == 0){
        stripOut(value);
        assignTok(tok,value,TYPE);
        token* tmpTok; tmpTok = newToken();
        tmpTok->prev = tok;
        tok->next = tmpTok;
        return tmpTok;
    }
        /* Case: token type META */
    else if (strcmp(TYPE,TMETA) == 0){
        assignTok(tok,value,TYPE);
        token* tmpTok; tmpTok = newToken();
        tmpTok->prev = tok;
        tok->next = tmpTok;
        return tmpTok;
    }
        /* Case: token type EOL */
    else if (strcmp(TYPE,TEOL) == 0){
        assignTok(tok,"EOL\0",TYPE); /* End of line token */
        tok->next = NULL;           /* End of line token marks end of list */
        lTok = tok;
        return tok;       /* End of linked list of tokens */
    }
    else{
        printf("Error: Token type does not match any expected values\n");
        return NULL;
    }
}

/* This helper function is designed to remove the Quotation marks
 From STRING type tokens.
 */
void stripOut(char* tokVal){
    int i; /* for loop index */
    for (i = 0;i<strlen(tokVal)-2;i++){
        tokVal[i] = tokVal[i+1];
    }
    tokVal[strlen(tokVal)-2] = '\0'; /* insert the new null terminating char */
}
/*stripper.c*/
