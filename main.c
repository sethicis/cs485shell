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
  //  printf("%s\n", fTok->type);
    lTok = fTok;  /* Only one token, thus first and last are the same */
    errFlag = 0; /* No errors seen yet */
    cPrompt = "iosh % \0";
    printf("%s ",cPrompt); /* Print the default prompt to the terminal */
   // printf("I went to the parser\n");
    while (scan() == 0) {
	//    printf("I'm in the while loop\n");
 /* While the EOF flag is not seen keep */
        if (debugFlag == 1) {
           // printf("I went to debug parse\n");		/* scanning and parsing */
            parse(); 
            debug();
        }           /* Parse the strings passed */
        else {
	 // printf("I went to parse\n");
          parse();
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
