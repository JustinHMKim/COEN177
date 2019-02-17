/*
 * # Name: Justin Kim
 *
 * # Date: 1/22/19 Tuesday labs
 *
 * # Title: Lab3 – Part 5
 *
 * # Description: This program has two producers send 10 messages each through a pipe to a consumer that prints the messages. 
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
  int i,j;
  pipe(fds);   
  if (fork()==0){//First Producer 
  	printf("\nWriter 1 on the upstream end of the pipe -> %d arguments \n",argc);
    close(fds[0]);
    dup2(fds[1],1);//stdout
    for(j=0;j<10;j++){//Write Producer 1 10 times
      write(fds[1],"Producer 1",strlen("Producer 1"));
    }
    exit(0);
  }
  else if(fork()==0){//Second Producer
    printf("\nWriter 2 on the downstream end of the pipe \n");
    close(fds[0]);
    for(i=0;i<10;i++){//Write Producer 2 10 times
      write(fds[1],"Producer 2", strlen("Producer 2"));
    }
    exit(0);
  }
  else if(fork()==0){//Consumer
    printf("\nReader on the downstream end of the pipe \n");
    close(fds[1]);
    while((count=read(fds[0],buff,60))>0){//access the pipe
      for(i=0;i<count;i++){
  	    write(1,buff+i,1);//print out from the pipe		
      }
  	printf("\n");
  	}
  }
  else{     
   	close(fds[0]);
    close(fds[1]);
    wait(0);
    wait(0);
  }
  return 0;
}
