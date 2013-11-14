/*
  tokenGen.c
 
  Created by Kyle Blagg on 11/8/13.
 This file contains the functions pretaining to the generation and population
 of new tokens.

*/

#include <stdio.h>      /* NOTE: May not be needed */
#include <stdlib.h>     /* for malloc */
#include <string.h>	/* Needed for strlen */
#include "global.h"     /* For global values */

/* This function generates a new token */
token* newToken(){
    token* mTok = (token*)malloc(sizeof(token));
    /* All these pointers are assigned the value NULL for safety reasons */
    mTok->val = NULL;
    mTok->type = NULL;
    mTok->next = NULL;
    mTok->prev = NULL;
    mTok->usage = NIL;  /* No usage yet */
    return mTok;
}

/* This helper function insures that the char* values get allocated
 and assigned on token Linage.
 */
void assignTok(token* tok,char* val,char* T){
    tok->val = (char*)malloc(strlen(val));
    strcpy(tok->val,val);
    tok->type = (char*)malloc(strlen(T));
    strcpy(tok->type,T);
}
