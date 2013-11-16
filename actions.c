/*
  actions.c
  Created by Kyle Blagg And Libby Ferland.
 
 The bulk of the action DO STUFF functions are located in this module,
 including the decide function which handles determining what actions to launch.
*/

#include <stdio.h>  /* For IO operations */
#include <string.h> /* For strcmp */
#include "global.h" /* For globally defined values */
#include <stdlib.h> /* For open and other system calls */
#include <unistd.h> /* For IO redirection */
#include <fcntl.h>  /* For file descriptor operations */

static long pathSize; /* Size of the char array to generate */

/* This function handle determining what actions to launch for the
 parsed tokens.  If the first token doesn't match any of the expected
 usage cases, then the decide() function does nothing.
 */
void decide(){
    /* If there are syntax errors then don't do anything */
    if (errFlag == 0) {
        switch (fTok->usage) {
            case SPROMPT:
                /* Gets the value of token after fTok and sets it as prompt */
                chPrompt(fTok->next->val); 
                break;

            case COMMENT:
                /* Do nothing */
                break;

            case DEBUG:
                if (strcmp(fTok->next->val,UON) == 0) {
                    debugFlag = 1;
                }
                else if (strcmp(fTok->next->val,UOFF) == 0) {
                    debugFlag = 0;
                }
                else{
                    /* The token value after debug was not of the expected form */
                    printf("-iosh: Illegal syntax. 'debug [on|off]' parameter passed was: %s\n",
                            fTok->next->val);
                }
                break;

            case CD:
                /* Change working directory, and if error notify */
                if (chdir(fTok->next->val) != 0) {
                    printf("-iosh: chdir %s Error."
                           "Directory %s either does not exist or cannot be accessed\n",
                           fTok->next->val,
                           fTok->next->val);
                }
                break;

            case CMD:
                handleCmd(); /* Take care of the command call */
                break;

            case IFILE:
                handleCmd(); /* If the first token's usage is IFILE, then it must be a command */
                break;

            case EOL:
                /*Do nothing */
                break;

            /*case QUIT:
                printf("This case shouldn't run...\n");
                terminate();
                break; This case should run in parse.*/
            default:
                /* Most likely a NIL or STRING or some other odd first token usage */
                /* Do nothing */
                break;
        }
        cleanup(); /* Remove unneeded tokens */
    }
}

/* This function handles preparing commands for execution.
 The function uses the parsed tokens and their assigned usages
 to determine the command to execute, the necessary arguments,
 and if necessary the input and output files for execution.
 The function prepares the command for execution by
 creating an array of arguments where the first element is the command name
 and the last is the null termination character.  This is for the execv
 call which is handled in exCmd().
 @RETURN: void
 */
void handleCmd(){
    int argc;
    char* iFile;
    char* oFile;
    char** mArgs;
    token* aTok;
    token* argTok;
    token* cmdTok;

    argc = 0; /* Number of arguments being passed to the cmd */
    iFile = NULL; 
    oFile = NULL;
    aTok = fTok; 
    argTok = NULL;
    cmdTok = NULL;

    /*Sort tokens by type */
    while (aTok != NULL){
        if (aTok->usage == IFILE) {
            iFile = aTok->val;
        }
        else if(aTok->usage == OFILE){
            oFile = aTok->val;
        }
        else if(aTok->usage == CMD){
            cmdTok = aTok;
        }
        else if(aTok->usage == ARG && argTok == NULL){
            if (argTok == NULL) /* Get the first argument token */
                argTok = aTok;
                argc++; /* Increment the count of arguments */
            }
        aTok = aTok->next; /* Keep doing this until end of token list */
    }

    /* Make argument array
     * First argument is always the program name
     * The malloc is set to argc + 2 because we will always have the program name and the null
     * terminating character in the array.  If we have any argument tokens, they go here. */
    mArgs = (char**)malloc(sizeof(char**)*(argc+2));
    mArgs[0] = cmdTok->val; 
  
    if (argTok != NULL) {
        int i; i = 1; /* index into argument array */
        while (argTok->usage == ARG) {
            mArgs[i++] = argTok->val;
            argTok = argTok->next;
        }
    }

    /* The last argument will always be the null terminator */
    mArgs[argc+1] = '\0';

    /* spawns the child process and starts the program with the given args */
    exCmd(mArgs,iFile,oFile);
}


/* This function is used to change the cPrompt
 for the ioShell
 @param str: The c string to set the cPrompt to.*/
void chPrompt(char* str){
    cPrompt = (char*)malloc(strlen(str)+1);
    cPrompt = str;
}


/* This function handles creating the child process,
 opening any file handles, and redirecting any I/O that needs
 to be redirected.
 @param mArgs: Array of command arguments where the first element is the cmd.
 @param iFile: Input file for the command.
 @param oFile: Output file for the command.
 */
void exCmd(char** mArgs,char* iFile,char* oFile){
    int pid;
    /* If file is executable. If it doesn't don't even bother */
    if (access(mArgs[0],X_OK) != -1){
        if ((pid = fork()) == 0) {
            if (iFile != NULL){
                /* Open the file as read only */
                int iFd = open(iFile,O_RDONLY);
                if (iFd < 0) {
                    printf("-iosh: IO Error. %s does not exist or is a directory\n",iFile);
                    exit(0); /* in File didn't exist terminate */
                }
                /* Set the STDIN of the child to the input file */
                dup2(iFd,STDIN_FILENO);
                close(iFd);
            }
            if (oFile != NULL){
                /*  Open the file as write only.
                 *  Clear all contents if file exists.
                 *  If the file doesn't already exist create it as
                 *  read and writeable by the user and readable by group.
                 */
                int oFd = open(oFile,O_WRONLY|O_TRUNC|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP);
                /* If file could not be opened error and terminate */
                if (oFd < 0){
                    printf("-iosh: IO Error: %s could not be opened or created\n",oFile);
                    exit(0);
                }
                dup2(oFd,STDOUT_FILENO); /* Redirect the output file to STDOUT */
                dup2(oFd,STDERR_FILENO);/* Write errors to file by redirecting STDERR */
                close(oFd); /* Don't need this anymore */
            }
            execv(mArgs[0],mArgs); /* Create start the program */
            /* If execv returned then it's because something went wrong */
            /* Terminate */
            exit(0);
        }
        wait(&pid); /* Wait for child to terminate */
    }else{
        printf("-iosh: IO Error: %s does not exist or is not executable\n",mArgs[0]);
    }
}

/* Allows for graceful termination of the shell program */
void terminate(){
    cleanup(); /* Makesure all the tokens in the linked list are destroyed */
    free(fTok); /* Release the dynamically allocated space for fTok */
    exit(0); /* Our work here is done. */
}

/* Deletes the dynamically allocated tokens */
void cleanup(){
    token* nTok;            /* Temporary token used for position tracking */
    if (lTok->prev != NULL){ /* While not fTok */
        nTok = lTok->prev;      /* Keep track of the parent token */
        free(lTok);             /* Release the dynamically allocated memeory */
        lTok = nTok;
    }
    /* All but the fTok values have been freed */
    errFlag = 0; /* Reset error flag */
}

/* Determines the current working directory */
void locate(){
    pathSize = pathconf(".",_PC_PATH_MAX); /* Gets the maximum path size of the machine */
    char* buf;
    if ((buf = (char*)malloc(pathSize)) != NULL){
        wkDir = getcwd(buf,(size_t)pathSize);
    }
}
/*actions.c*/
