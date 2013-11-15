
/*  Debug.c
 

  Created by Kyle Blagg and Libby Ferland on 11/11/13.
  This module is used to traverse the linked list and output
    the debug info.
*/

#include <stdio.h>
#include "global.h"
#include <stdlib.h>

/* Simple parse function that traverses the linked list and prints out
 the token type and value until the end of list is reached */
void debug(){
    int count = 1;
    char* tokU;
    token* tok = fTok;
    while (tok != NULL) {
        printf("\t\tToken #: %d\n",count);
        printf("\t\tToken Type: %s\n",tok->type);
        switch (tok->usage) {
            case NIL:
                tokU = "NULL\0";
                break;
            case COMMENT:
                tokU = "COMMENT\0";
                break;
            case SPROMPT:
                tokU = "SETPROMPT\0";
                break;
            case DEBUG:
                tokU = "DEBUG\0";
                break;
            case CD:
                tokU = "CHDIR\0";
                break;
            case CMD:
                tokU = "CMD\0";
                break;
            case IFILE:
                tokU = "InFile\0";
                break;
            case OFILE:
                tokU = "OutFile\0";
                break;
            case META:
                tokU = "META\0";
                break;
            case QUIT:
                tokU = "QUIT\0";
                break;
            case STRING:
                tokU = "STRING\0";
                break;
            case WORD:
                tokU = "WORD\0";
                break;
            case ARG:
                tokU = "ARG\0";
                break;
            default:
                tokU = "EOL\0";
                break;
        }
        printf("\t\tToken Usage: %s\n",tokU);
        printf("\t\tToken Value: %s\n\n",tok->val);
        tok = tok->next;
        count++;
    }
}
