/*
 stripper.c
 
  Created by Kyle Blagg on 11/8/13.

*/

#include <stdio.h>
#include <string.h>
#include "global.h"

token* strip(char* match, char* strTok){
    token* tok = newToken();
    char* str = stripOut(match,strTok);
    char* str = stripOut('"',str);
}

char* stripOut(char* match, char* strTok){
    int first = -1,second = -1,terminate = 0;
    /* int terminate = 0; */
    for (int i=0; i<sizeof(strTok); i++) {
        if (first == -1) {
            if (strTok[i] == match[0]) {
                first = i;
            }
        }
        else if(second == -1){
            if (strTok[i] == match[sizeof(match)-1]){
                second = i;
            }
        }
        else{
            terminate = 1;
        }
    }
    if (terminate != 1) {
        /* char* str[1];
        return str[0] = '\0'; */
        return strTok;
    }else{
        int size = second - first;
        char* str[size+1];
        strncpy(str,strTok[first],size);
        str[sizeof(str)-1] = '\0';
        return str;
    }
}