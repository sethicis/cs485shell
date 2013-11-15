/*
 *  pTest.c
 
 
 *  Created by Kyle Blagg on 11/11/13.
 *  Edited by Libby Ferland on 11/14/13.
 *  This module is used for testing the token linked list
 *  and can be used as an example for how to traverse the linked list.
 *  This module handles system commands and error handling.
 */

#include <stdio.h>
#include "global.h"
#include <stdlib.h>
#include <string.h>

/* Simple parse function that traverses the linked list and prints out
 the token type and value until the end of list is reached */
void parse(){
    /*int count = 1; TO BE REMOVED */
    printf("In parser()\n");
    token* reader = fTok;
    while (reader != NULL) {
        /*Recognize comment lines*/
        if (strcmp(fTok->val, UPOUND) == 0) {
            reader->usage = COMMENT;
            /* If the first token is a # then all tokens till EOL are comments */
            while (reader->next != NULL) {
                reader->usage = COMMENT;
                reader = reader->next;
            }
            /* End of line token */
            reader->usage = EOL;
            reader = reader->next;
        }
        
        /*Recognize setprompt*/
        else if (strcmp(reader->val, USETPROMPT) == 0) {
            reader->usage=SPROMPT;
            reader = reader->next;
            if (strcmp(reader->type, TSTRING) != 0) {
                printf("-iosh: Cannot set prompt without a string!\n");
                errFlag = 1;
                while (reader->next != NULL) {
                    reader = reader->next;
                    /* All token usages are undefined until EOL */
                }
                reader->usage = EOL; /* End of line token */
                reader = reader->next;/* Set to null to leave while loop */
            }
            else {
                reader->usage = STRING;
                reader = reader->next;
                if (strcmp(reader->type, TEOL) != 0) {
                    printf("-iosh: Cannot take multiple arguments in setprompt!\n");
                    errFlag = 1; /* Flag fTok for error */
                    while (reader->next != NULL) {
                        reader = reader->next;
                        /* All token usages are undefined until EOL */
                    }
                    reader->usage = EOL;
                    reader = reader->next; /* Set to null to leave while loop */
                }
                else {
                    reader->usage = EOL;
                    reader = reader->next; /* Set to null to leave while loop */
                }
            }
        }
        
        /*Recognize chdir*/
        else if (strcmp(reader->val, UCHDIR) == 0) {
            reader->usage = CD;
            reader = reader->next;
            if (strcmp(reader->type, TMETA) == 0) {
                reader->usage = META;
                printf("-iosh: Cannot use a metacharacter in chdir command.\n");
                errFlag = 1; /* Set error flag */
                while (reader->next != NULL) {
                    reader = reader->next;
                    /* All token usages are undefined until EOL */
                }
                reader->usage = EOL;
                reader = reader->next; /* Leave while loop */
            }
            else if (strcmp(reader->type, TEOL) == 0) {
                reader->usage = EOL;
                printf("-iosh: You must enter a directory name!\n");
                errFlag = 1; /* Flag for error */
            }
            else {
                reader->usage = ARG;
                reader = reader->next;
                if (strcmp(reader->type, TEOL) != 0) {
                    printf("-iosh: Cannot handle multiple arguments in a chdir request.\n");
                    errFlag = 1; /* Flag for error */
                    while (reader->next != NULL) {
                        reader = reader->next;
                        /* All token usages are undefined until EOL */
                    }
                    reader->usage = EOL;
                    reader = reader->next; /* leave while loop */
                }
                else {
                    reader->usage = EOL;
                    reader = reader->next; /* leave while loop */
                }
            }
        }
        /* Case Debug */
        else if (strcmp(reader->val, UDEBUG) == 0) {
            reader->usage = DEBUG;
            reader = reader->next;
            if (strcmp(reader->type, TEOL) == 0) {
                printf("-iosh: debug: Unknown debug command.  Debug can be turned on or off.\n");
                /* syntax error: Token usage is undefined until EOL */
                errFlag = 1;
            }
            else if (strcmp(reader->type,TWORD) == 0){
                reader->usage = WORD;
                reader = reader->next;
            }
            else {
                printf("-iosh: debug: Unknown debug command.  Debug can be turned on or off.\n");
                errFlag = 1; /* Set error flag */
                /* Syntax error means usage is undefined for all but EOL */
                while (reader->next != NULL){
                    reader = reader->next;
                }
            }
            if (reader->next != NULL) {
                printf("-iosh: debug: Unknown debug command.  Debug can be turned on or off.\n");
                errFlag = 1; /* Set error flag */
                /* Syntax error means usage is undefined for all but EOL */
            }
            reader->usage = EOL;
            reader = reader->next; /* Leave while loop */
        }
        /* Case QUIT */
        else if (strcmp(reader->val, UQUIT) == 0) {
            reader->usage = QUIT;
            reader = reader->next;
                if (strcmp(reader->type, TEOL) != 0) {
                    printf("-iosh: Unrecognized command.  To quit, type 'quit' and press enter.\n");
                    errFlag = 1; /* Set error flag */
                }
            while (reader->next != NULL){
                reader = reader->next;
                /* All non EOL tokens are undefined in this context */
            }
            reader->usage = EOL;
            terminate(); /* No need to analyze this, we know what to do... */
        }
  else {
      /*token?*/
      while (reader->next != NULL) {
        if (strcmp(reader->type, TMETA) == 0) {
          if (reader->prev == NULL) {
            printf("-iosh: Illegal syntax.  Metacharacters cannot occur at the beginning of a line.\n");
          }
          else if (strcmp(reader->next->type, TMETA) == 0) {
            printf("-iosh: Illegal syntax.  Cannot have two adjacent metacharacters.\n");
          }
          reader->usage = META;
        }
       
        else if (strcmp(reader->type, TSTRING) == 0) {
          if (reader->prev == NULL) {
            printf("-iosh: Illegal syntax.  Cannot parse string literal as first token.");
          }
          else {
            reader->usage = STRING;
          }
        }

        else if (strcmp(reader->type, TWORD) == 0) {
          if (reader->prev == NULL) {
            reader->usage = CMD;
          }
          else if (strcmp(reader->next->val, LTHAN) == 0) {
            reader->usage = IFILE;
          }
          else if (strcmp(reader->next->val, GTHAN) == 0) {
            reader->usage = CMD;
          }
          else if (strcmp(reader->prev->val, LTHAN) == 0) {
            reader->usage = CMD;
          }
          else if (strcmp(reader->prev->val, GTHAN) == 0) {
            reader->usage = OFILE;
          }
          else {
            reader->usage = ARG;
          }
        }
        reader = reader->next;
      }
  }
}
    printf("End of parse...\n");
}
