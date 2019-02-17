/*
 * # Name: Justin Kim
 *
 * # Date: 1/22/19 Tuesday labs
 *
 * # Title: Lab3 – Part 4
 *
 * # Description: This program implements cat /etc/passwd | grep root in C.  
 * 
 * */

/*Sample C program for Lab assignment 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 
#include <sys/types.h> 
#include <sys/ipc.h>
// main
int main(int argc,char *argv[]){
    int  fds[2];
    char buff[60];
    int count;
    int i;
    pipe(fds);   
    if (fork()==0){
    	printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
        close(fds[0]);
        dup2(fds[1],1);//stdout
	    execlp("cat", "cat", "/etc/passwd", 0);//the cat command on /etc/passwd; gets contents of /etc/passwd file
        exit(0);
    }
    else if(fork()==0){
    	printf("\nReader on the downstream end of the pipe \n");
    	close(fds[1]);
    	dup2(fds[0],0);//stdin
    	execlp("grep","grep","root",0);//the grep command on root; searches for root in the input from the pipe, that being the output of cat etc/passwd
    	printf("\n");
    	exit(0);
    }
    else{     
   	    close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}
