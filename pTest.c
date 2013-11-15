/*
*  pTest.c
  

*  Created by Kyle Blagg on 11/11/13.
*  This module is used for testing the token linked list
*  and can be used as an example for how to traverse the linked list.
*/

#include <stdio.h>
#include "global.h"
#include <stdlib.h>

/* Simple parse function that traverses the linked list and prints out
 the token type and value until the end of list is reached */
void parse(){
    int count = 1;
    token* tok = fTok;
    token* lTok = NULL;
    while (tok != NULL) {
        printf("\t\tToken #: %d\n",count);
        printf("\t\tToken Type: %s\n",tok->type);
        printf("\t\tToken Value: %s\n",tok->val);
        printf("\t\tToken Usage: %d\n",tok->usage);
        if (tok->next == NULL){ /* Keep track of the last token to save
                                 computation time when deleting */
            lTok = tok;
        }
        tok = tok->next;
        count++;
    }
    cleanup(lTok); /* Remove the no longer needed tokens */
}
