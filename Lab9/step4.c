/*
 * *#Name: Justin Kim
 * *# Date: 3/5/19 Tuesday labs
 * *# Title: Lab 9 Step 4
 * * Description: This program reads from 100k, 1m, 10m, and 100m files to a buffer with user set size and writes from the buffer to files using multithreading 
* */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{//allows for tracking both thread number and user inputs
    int iter;
    char **v;
} arguments;

void *go(void *arg) {
    arguments *argu = (arguments *) arg;
    int count = (*argu).iter;
    int MAXBUFLEN = atoi((*argu).v[2]);
    int buff[MAXBUFLEN];
    char *file = (*argu).v[1];
    FILE *fp = fopen(file,"rb");
    char filename[20];
    sprintf(filename, "T%d--%sstep4result%d.bin",count, file,MAXBUFLEN);//names each copy according to file, buff size, and thread number
    //printf("%s \n", filename);
    FILE *wp = fopen(filename,"wb");
    while(fread(buff,MAXBUFLEN,1,fp)){
        fwrite(buff, MAXBUFLEN,1,wp);
    }
    fclose(fp);
    fclose(wp);
    return (NULL);
}

int main(int argc, char *argv[]){
    arguments argument;
    int NTHREADS = atoi(argv[3]);//set number of threads
    pthread_t threads[NTHREADS];
    int i;
    argument.v = argv;
    for (i = 0; i < NTHREADS; i++){//creates the threads, specifies the thread number
        argument.iter = i;
        pthread_create(&threads[i], NULL, go, &argument);
    }
    for (i = 0; i < NTHREADS; i++){
        pthread_join(threads[i],NULL);
        //printf("Thread %d returned \n", (void*)i);
    }
    return 0;
}
        
