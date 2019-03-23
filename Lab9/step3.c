/*
 * *#Name: Justin Kim
 * *# Date: 3/5/19 Tuesday labs
 * *# Title: Lab 9 Step 4
 * * Description: This program reads from 100k, 1m, 10m, and 100m files to a buffer with user set size and writes from the buffer to files 
* */


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int MAXBUFLEN = atoi(argv[2]);
    char buff[MAXBUFLEN];
    FILE *fp = fopen(argv[1], "rb");
    char filename[20];
    sprintf(filename, "%sstep3result%d.bin", argv[1],MAXBUFLEN);//names files to be written so they don't overwrite each other
    FILE *wp = fopen(filename,"wb");
    while(fread(buff,MAXBUFLEN,1,fp)){
        fwrite(buff, MAXBUFLEN,1,wp);
    }
    fclose(fp);
    fclose(wp);
    return 0;
}
        
