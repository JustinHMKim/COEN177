/*
 * *#Name: Justin Kim
 * *# Date: 3/5/19 Tuesday labs
 * *# Title: Lab 9 Step 4
 * * Description: This program reads from 100k, 1m, 10m, and 100m files to a buffer with user set size and writes from the buffer to files using multithreading 
* */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int MAXBUFLEN = atoi(argv[2]);
    int buff[MAXBUFLEN];//adds buffer size
    FILE *fp = fopen(argv[1], "rb");
    while(fgets(buff,MAXBUFLEN,fp)){}
    fclose(fp);
    return 0;
}
        
