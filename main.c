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
    lTok = fTok;  /* Only one token, thus first and last are the same */
    errFlag = 0; /* No errors seen yet */
    cPrompt = "iosh % \0";
    printf("%s ",cPrompt); /* Print the default prompt to the terminal */
    while (scan() == 0) { /* While the EOF flag is not seen keep 
                           scanning and parsing */
        parse();           /* Parse the strings passed */
        if (debugFlag == 1) {
            debug();
        }
        /* Determine what actions to take based on parser assigned usages to tokens */
        decide();
        //printf("Returned from Decide()\n");
        printf("%s ",cPrompt);
        //printf("After prompt\n");
    }
    printf("Exitting\n");
    terminate();      /* Clean up the last memory leak */
    /*free(wkDir);   */
    return 0;
}
