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
    token* tok = fTok;
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

  else if (strcmp(reader->val, UDEBUG) == 0) {
    reader = reader->next;
    reader = reader->next;
    tok = tok->next;
    if (strcmp(reader->type, TEOL) != 0) {
      printf("-iosh: debug: Unknown debug command.  Debug can be turned on or off.\n"); }
    else if (strcmp(tok->val, UON) == 0) {
      printf("debug: Turning debug ON. \n");
      /*do something here*/
      }
    else if (strcmp(tok->val, UOFF) == 0) {
      printf("debug: Turning debug OFF. \n");
      /*do something else here*/
    }
    else {
      printf("-iosh: debug: Unknown debug command.  Debug can be turned on or off.\n");  
    }
   }

  while (tok->next != NULL) {
    tok = tok->next;
  }

		/*
        if (tok->next == NULL){ /
            lTok = tok;
        }
        tok = tok->next;
        count++;*/
    cleanup(); /* Remove the no longer needed tokens */
}
}
