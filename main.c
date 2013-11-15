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

int main(int argc,char** argv){
    /* Find out where our working directory is */
    locate();
    /* Initalize fTok on startup */
    fTok = newToken();
    cPrompt = (char*)malloc(sizeof("iosh % \0"));
    cPrompt = "iosh %";
    printf("%s ",cPrompt); /* Print the default prompt to the terminal */
    while (scan() == 0) { /* While the EOF flag is not seen keep 
                           scanning and parsing */
        parse();           /* Parse the strings passed */
        decide();   /* Determine what actions to take based on parser assigned usages to tokens */
        printf("%s ",cPrompt);
    }
    terminate();      /* Clean up the last memory leak */
    /*free(wkDir);   */
    return 0;
}
