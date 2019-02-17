/*
 * # Name: Justin Kim
 *
 * # Date: 1/22/19 Tuesday labs
 *
 * # Title: Lab3 – Part 3
 *
 * # Description: This program prints out the other files in the same directory as it, with spaces between each character. 
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
        for(i=0;i<argc;i++){
        	dup2(fds[1],1);
		execlp("ls", "ls", 0);//the ls command, prints out contents of current directory
        }
        exit(0);
    }
    else if(fork()==0){
    printf("\nReader on the downstream end of the pipe \n");//same as Part 2
    close(fds[1]);
    	while((count=read(fds[0],buff,60))>0){
        	for(i=0;i<count;i++){
        		write(1,buff+i,1);
                	write(1," ",1);
        	}
        }
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
