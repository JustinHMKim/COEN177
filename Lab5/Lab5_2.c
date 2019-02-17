/*
 * *#Name: Justin Kim
 * *# Date: 2/5/19 Tuesday labs
 * *# Title: Lab4 - Step 3
 * * Description: This program solves the producer-consumer problem with synchronization primitives, namely semaphores. 
 * */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define BUF_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 10

pthread_t threads[NUM_PRODUCERS+NUM_CONSUMERS];//the buffer for the producers and consumers

int producer_index = 0;
int consumer_index = 0;
sem_t full;
sem_t empty;
sem_t mutex;
int Buf[BUF_SIZE];

int irand(int start, int end){//provides a random integer for populating the matrices, provided by TA
    int range = end - start + 1;
    return rand() % range + start;//range != rand
}

void* prod(void* arg){
    do {
        int data = irand(0,10);//produce next item
        sem_wait(&empty);//P(), checks if empty is positive (that the buffer has space to write to), which lets the thread access critical region, and then increments down if so
        sem_wait(&mutex);//P() where mutex=1, so only one thread produce at a time
        Buf[producer_index]=data;//add the item to buffer
        printf("Producer %d | Produced item %d, stored in buff at index %d. \n", (int)arg,data, producer_index);
        if(producer_index<BUF_SIZE-1){
            producer_index++;
        }
        else{
            producer_index = 0;//wraps around array once it runs through the whole array
        }
        fflush(stdout);        
        sem_post(&mutex);//V(), increments up, allowing another thread to access critical region
        sem_post(&full);//V(), increments up, indicates the buffer has had an entry added and has one fewer space to write to
    } while (1);
}

void* cons(void* arg){
    do { 
        sem_wait(&full);//P(), checks if full is positive (that the buffer has entries to consume), which lets the thread access critical region, and then increments down if so
        sem_wait(&mutex);//P(), where mutex=1, so only one thread produce at a time
        int stuff = Buf[consumer_index];//'consumes' the next item, technically only reads and increments, entries get overwritten by producer instead
        printf("Consumer %d | Got item %d from buff index %d. \n", (int)arg, stuff, consumer_index);
        if(consumer_index<BUF_SIZE-1){
            consumer_index++;
        }
        else{
            consumer_index = 0;//wraps around array once it runs through the whole array
        }
        fflush(stdout);
        sem_post(&mutex);//V(), increments up, allowing another thread to access critical region
        sem_post(&empty);//V(), increments up, indicates the buffer has had an entry consumed and has one more space to write to
    } while (1);
}

int main(){
    sem_init(&full, 0, 0);//initialise the semaphores
    sem_init(&empty, 0, BUF_SIZE);
    sem_init(&mutex, 0, 1);
    int i;
    for (i = 0; i < NUM_PRODUCERS; i++){//creates producer threads
        pthread_create(&threads[i], NULL, prod, (void *)(size_t)i);
    }
    for (i; i < NUM_CONSUMERS+NUM_PRODUCERS; i++){//creates consumer threads
        pthread_create(&threads[i], NULL, cons, (void *)(size_t)i);
    }
    for (i = 0; i < NUM_CONSUMERS+NUM_PRODUCERS; i++){//waits for each thread to terminate before finishing
        pthread_join(threads[i],NULL);
    }
    return 0;
}
