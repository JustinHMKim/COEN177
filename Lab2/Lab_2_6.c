/*
# Name: Justin Kim

# Date: 1/15/19 Tuesday labs

# Title: Lab2 – Part 6

# Description: This program runs two threads that print one of 'parent' or 'child' process and the iteration number 100 times.
*/

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
#include <pthread.h>
/*main function with command-line arguments to pass */

void *process(void *voidptr){//the second thread operation
    int i;
    for (i = 0; i<100;i++){
        printf("Second Thread %d \n",i);
        usleep(3000);
    }
}
int main() {
    pthread_t  thid;
    if (pthread_create(&thid, NULL, &process, NULL) != 0) {//launches the second thread
        perror("pthread_create() error");
        exit(1);
    }
 	for (int i=0;i<100;i++) {
        printf("\t \t \t First Thread %d \n",i);
        usleep(3000);
	}								
	return 0;
} 
