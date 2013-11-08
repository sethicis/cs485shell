/*
  tokenGen.c
 
  Created by Kyle Blagg on 11/8/13.

*/

#include <stdio.h>
#include <stdlib.h>
#include "global.h"

token* newToken(){
    token* mTok = (token)malloc(sizeof(token));
    mTok->val = (char*)malloc(MAXBUFF);
    mTok->type = (char*)malloc(TYPEBUFF);
    mTok->next = NULL;
    return mTok;
}