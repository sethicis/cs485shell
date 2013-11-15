/*
*  pTest.c
  

*  Created by Kyle Blagg on 11/11/13.
*  This module is used for testing the token linked list
*  and can be used as an example for how to traverse the linked list.
*/

#include <stdio.h>
#include "global.h"
#include <stdlib.h>
#include <string.h>

/* Deletes the dynamically allocated tokens */
void cleanup(token* lTok){
    token* nTok;            /* Temporary token used for position tracking */
    if (lTok->prev != NULL){ /* While not fTok */
        nTok = lTok->prev;      /* Keep track of the parent token */
        free(lTok);             /* Release the dynamically allocated memeory */
        lTok = nTok;
    }
    /* All but the fTok values have been freed */
}
/* Simple parse function that traverses the linked list and prints out
 the token type and value until the end of list is reached */
void parse(){
    int count = 1;
    token* tok = fTok;
    token* lTok = NULL;
    token* reader = fTok;
    while (tok != NULL) {

/*Recognize comment lines*/
    if (strcmp(reader->val, UPOUND) == 0) {
      while (tok->next != NULL) {
        tok = tok->next;
      }
    }

/*Recognize setprompt*/
    else if (strcmp(reader->val, USETPROMPT) == 0) {
      reader = reader->next;
      if (strcmp(reader->type, TSTRING) != 0) {
        printf("-iosh: Cannot set prompt without a string!\n");
      }
      else {
        reader = reader->next;
        if (strcmp(reader->type, TEOL) != 0) {
          printf("-iosh: Cannot take multiple arguments in setprompt!\n");
        }
        else {
	  printf("debug: I will set your prompt\n");
        }
      } 
   }

/*Recognize chdir*/
    else if (strcmp(reader->val, UCHDIR) == 0) {
      reader = reader->next;
      if (strcmp(reader->type, TMETA) == 0) {
	printf("-iosh: Cannot use a metacharacter in chdir command.\n");
      }
      else if (strcmp(reader->type, TEOL) == 0) {
	printf("-iosh: You must enter a directory name!\n");
      }
      else {
	reader = reader->next;
	if (strcmp(reader->type, TEOL) != 0) {
          printf("-iosh: Cannot handle multiple arguments in a chdir request.\n");
	}
	else {
	  printf("debug: I will change directory.\n");
        }
      }
    }  

  while (tok->next != NULL) {
    tok = tok->next;
  }

			
        if (tok->next == NULL){ /* Keep track of the last token to save
                                 computation time when deleting */
            lTok = tok;
        }
        tok = tok->next;
        count++;
    cleanup(lTok); /* Remove the no longer needed tokens */
}
}
