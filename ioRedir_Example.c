/* This is an example program for file IO redirection */

#include <stdio.h> /* Used for IO actions */
#include <stdlib.h> /* used for open() and exec calls */
#include <unistd.h> /* For file handles dup2() */
#include <fcntl.h> /* For fork() and file operations */

int pid; /* Used to keep track of child proc ID */
char* mFILE = "example.txt"; /* File containing the info to redirect */
char* mPROG = "/bin/cat"; /* Program to call */
char* mARGS[2] = {"cat",0}; /* Arguments for mPROG needs mPROG name as mARGS[0] */

int main(int argc,char** argv){
	/* The child process gets its STDIN redirected to mFILE */
	if((pid = fork()) == 0){ 
		int fdIn = open(mFILE,O_RDONLY); /* Open mFILE */
		dup2(fdIn,STDIN_FILENO); /* Redirect the mFILE pointer to STDIN*/
		close(fdIn); /* Close it up */
		execl(mPROG,mARGS[0],mARGS[1]); /* Calls PROG, with ARGS */
	}
	wait(&pid);
	return 0;
}
	
	

