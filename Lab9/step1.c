/*
 * *#Name: Justin Kim
 * *# Date: 3/5/19 Tuesday labs
 * *# Title: Lab 9 Step 4
 * * Description: This program reads from 100k, 1m, 10m, and 100m files to a 10000 byte buffer 
* */
#include <stdio.h>
#include <stdlib.h>

#define MAXBUFLEN 10000


int main(int argc, char *argv[]){
    int buff[MAXBUFLEN];
    FILE *fp = fopen(argv[1], "rb");
    while(fgets(buff,MAXBUFLEN,fp)){}//just reads the files
    fclose(fp);
    return 0;
}
        
