/* 
This file right now works as a test driver for the Unix shell program.
In it's current incarnation it only calls the scan function to test the flex
file, but it may be expanded in the future. This entry point could be modified
to work as an entry point for the finished program as well.
*/
#include "global.h"

int main(int argc,char** argv){
	if (scan() == 0)
		printf("Exitting Successfully!\n");
	else
		printf("ERROR! Exitting!\n");
	return 0;
}