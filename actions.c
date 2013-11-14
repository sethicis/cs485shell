/*
  actions.c
 
  Created by Kyle Blagg And Libby Ferland.

*/

#include <stdio.h>

/* This function is used to change the cPrompt
 for the ioShell
 @param str: The c string to set the cPrompt to.*/
void chPrompt(char* str){
    free(cPrompt);
    cPrompt = str;
}

