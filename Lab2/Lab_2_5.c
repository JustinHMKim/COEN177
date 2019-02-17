/*
# Name: Justin Kim

# Date: 1/15/19 Tuesday labs

# Title: Lab2 – Part 5

# Description: This program outputs a balanced binary tree with 7 nodes, each node being a process. 
*/

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 

int main(){
	pid_t pid0, pid1, pid2, pid3, pid4, pid5, pid6;//declaring the processes in advance
	printf("Parent of all: %d\n",getpid());
	pid0 = fork();//first branch/fork, then their branch/forks
        if (pid0 == 0) {//checks that there's no children, repeated for the children for their children
		printf("1.Child with id: %d and its Parent id: %d \n", getpid(), getppid());
		pid1 = fork();
		if (pid1==0){ 
			printf("2.Child with id: %d and its Parent id: %d \n", getpid(), getppid());
		}
		if (pid1 >0){
		pid5 = fork();
		if (pid5 ==0){
			printf("7.Child with id: %d and its Parent id: %d \n", getpid(), getppid());
			}
		}	
	}
	else if (pid0>0){//second branch/fork, then their branch/forks
		pid2 = fork();
		if (pid2==0){//checks that there's only one other child, repeated for the children for their children
			printf("5.Child with id: %d and its Parent id: %d \n", getpid(), getppid());
			pid3 = fork();
			if (pid3 == 0){	
				printf("4.Child with id: %d and its Parent id: %d \n", getpid(), getppid());
			}
			if (pid3 >0 ){
			pid4 = fork();
				if (pid4 ==0){
					printf("6.Child with id: %d and its Parent id: %d \n", getpid(), getppid());
				}
			}
		}		
	}
	for(int i=0;i<4;i++){//set a delay to ensure the program runs correctly, otherwise pid 1 ends up being the parent of one of the processes instead of one of the pid_t declared above
		wait(500);
	}
}
