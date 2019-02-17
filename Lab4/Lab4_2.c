/*
 * #Name: Justin Kim
 *
 *# Date: 1/29/19 Tuesday labs
 *
 *# Title: Lab4 - Step 2
 *
 *
 * Description: This program removes pthread_join to demonstrate the effect of the parent thread not waiting on the child threads to all finish before ending. 
 *
 * */

/**************************************************************
*	threadHello.c - simple multi-threaded program.            *
*   compile with: >gcc -lpthread threadHello.c -o threadHello *
*   Winter 2019                                               *
**************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 10

void *go(void *);
pthread_t threads[NTHREADS];

int main() {
    static int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    printf("Main thread done.\n");//no pthread_join below
}
void *go(void *arg) {
    printf("Hello from thread %d with thread ID %d \n", (int)arg, (int)pthread_self());
    return (NULL);
}

