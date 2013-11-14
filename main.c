/* 
 main.c
 
 This is the entry point function for the Unix Shell Project for
 CS 485.
 Created by Libby and Kyle
 
 This module initalizes the first Token
 
*/

#include <stdio.h>  /* Used for I\O */
#include <stdlib.h> /* Used for malloc */
#include "global.h" /* Used for global variables */

/* This function is used to change the cPrompt
 for the ioShell
 @param str: The c string to set the cPrompt to.*/
void chPrompt(char* str){
    free(cPrompt);
    cPrompt = str;
}

int main(int argc,char** argv){
    /* Initalize fTok on startup */
    fTok = newToken();
    cPrompt = (char*)malloc(sizeof("iosh % \0"));
    cPrompt = "iosh %";
    printf("%s ",cPrompt); /* Print the default prompt to the terminal */
    while (scan() == 0) { /* While the EOF flag is not seen keep 
                           scanning and parsing */
        parse();
        printf("%s ",cPrompt);
    }
	printf("Exitting!\n");  /* TODO: Remove print statement */
    free(fTok);             /* Clean up the last memory leak */
    return 0;
}
