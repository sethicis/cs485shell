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
    while (tok != NULL && reader != NULL) {
        
        /*Recognize comment lines*/
  if (strcmp(reader->val, UPOUND) == 0) {
    reader->usage = COMMENT;
    while (tok->next != NULL) {
      tok = tok->next;
    }
      }
        
        /*Recognize setprompt*/
  else if (strcmp(reader->val, USETPROMPT) == 0) {
    reader->usage=SPROMPT;
    reader = reader->next;
    if (strcmp(reader->type, TSTRING) != 0) {
        printf("-iosh: Cannot set prompt without a string!\n");
    }
    else {
      reader->usage = STRING;
      reader = reader->next;
      if (strcmp(reader->type, TEOL) != 0) {
        printf("-iosh: Cannot take multiple arguments in setprompt!\n");
      }
      else {
        reader->usage = EOL;
        printf("debug: I will set your prompt\n");
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
    }
    else if (strcmp(reader->type, TEOL) == 0) {
      reader->usage = EOL;
      printf("-iosh: You must enter a directory name!\n");
    }
    else {
      reader->usage = ARG;
      reader = reader->next;
      if (strcmp(reader->type, TEOL) != 0) {
        printf("-iosh: Cannot handle multiple arguments in a chdir request.\n");
      }
      else {
        reader->usage = EOL;
        printf("debug: I will change directory.\n");
      }
    }
  }
        
  else if (strcmp(reader->val, UDEBUG) == 0) {
    reader->usage = DEBUG;
    reader = reader->next;
    reader = reader->next;
    tok = tok->next;
    if (strcmp(reader->type, TEOL) != 0) {
      printf("-iosh: debug: Unknown debug command.  Debug can be turned on or off.\n"); }
    else if (strcmp(tok->val, UON) == 0) {
      printf("debug: Turning debug ON. \n");
      tok->usage = WORD;
                /*do something here*/
    }
    else if (strcmp(tok->val, UOFF) == 0) {
      printf("debug: Turning debug OFF. \n");
      tok->usage = WORD;
                /*do something else here*/
    }
    else {
      printf("-iosh: debug: Unknown debug command.  Debug can be turned on or off.\n");  
    }
  }
  
  else if (strcmp(reader->val, UQUIT) == 0) {
    reader->usage = QUIT;
    reader = reader->next;
    if (strcmp(reader->type, TEOL) != 0) {
      printf("-iosh: Unrecognized command.  To quit, type 'quit' and press enter.\n");
    }
    else {
      reader->usage = EOL;
    }
  }
  
  else {
    reader->usage = EOL;
  }
  /*token?*/      
  while (reader->next != NULL && tok->next != NULL) {
    if (strcmp(reader->type, TMETA)) {
      if (reader->prev == NULL) {
        printf("-iosh: Illegal syntax.  Metacharacters cannot occur at the beginning of a line.\n");
      }
      else if (strcmp(reader->next->type, TMETA) == 0) {
        printf("-iosh: Illegal syntax.  Cannot have two adjacent metacharacters.\n");
      }
      reader->usage = META;
    }
   
    else if (strcmp(reader->type, TSTRING)) {
      if (reader->prev == NULL) {
        printf("-iosh: Illegal syntax.  Cannot parse string literal as first token.");
      }
      else if (strcmp(reader->next->val, LTHAN) == 0) {
        reader->usage = IFILE;
      }
      else {
        reader->usage = STRING;
      }
    }

    else if (strcmp(reader->type, TWORD)) {
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
   
    tok = tok->next;
    reader = reader->next;
  }
    cleanup(); /* Remove the no longer needed tokens */
} 
}
