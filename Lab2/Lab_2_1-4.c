/*
# Name: Justin Kim

# Date: 1/15/19 Tuesday labs

# Title: Lab2 – Parts 1-4

# Description: This program runs two processes that print one of 'parent' or 'child' process and the iteration number 100 times. It was provided
and required no additional additions to run properly. 
*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
/*main function with command-line arguments to pass */

int main(int argc, char *argv[]) {
    pid_t  pid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before forking.\n");
    pid = fork();//forking
    if (pid == -1) {//error if it doesn't fork
        fprintf(stderr, "can't fork, error %d\n", errno);
    } 
    if (pid){
	// Parent process
	for (i=0;i<100;i++) {
		printf("\t \t \t Parent Process %d \n",i);
		usleep(n);
		}
	}
    else{
	// Child process
	for (i=0;i<100;i++) {
		printf("Child process %d\n",i); 
		usleep(n);
		}
	}
	return 0;
} 
