/* 
 main.c
 
 This is the entry point function for the Unix Shell Project for
 CS 485.
 Created by Libby and Kyle
 
 This module initalizes the first Token, links the Token list, sends the tokens to the parser, and han dles graceful exit.
 
*/

#include <stdio.h>  /* Used for I\O */
#include <stdlib.h> /* Used for malloc */
#include "global.h" /* Used for global variables */

int main(int argc,char** argv){
    	
    /*Initialize main function handlers
     * 1. Find current directory
     * 2. Intialize first Token for linked list
     * 3.  Link list
     * 4.  Set error flags and default prompt */
    locate();
    fTok = newToken();
    lTok = fTok;  /* Only one token, thus first and last are the same */
    errFlag = 0; 
    cPrompt = "iosh % \0";
    printf("%s ",cPrompt); 

    /*Begin scanning and sending data to parser.  While the scanner returns 0 (found EOL, not EOF),
     * parse each line with debugging information as necessary.  Decide what to do with the tokens
     * and execute user instructions */
    while (scan() == 0) {

        if (debugFlag == 1) {
            parse(); 
            debug();
        }           
        else {
            parse();
        }
    
        decide();
        printf("%s ",cPrompt);
    }
    
    printf("Exiting\n");
    terminate();      /* Clean up the last memory leak */
    /*free(wkDir);   */
    return 0;
}
/*int main() */
