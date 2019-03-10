/*
 * *#Name: Justin Kim
 * *# Date: 2/26/19 Tuesday labs
 * *# Title: Lab 8 FIFO
 * * Description: This program implements the FIFO algorithm 
* */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int CACHE_SIZE = atoi(argv[1]);//cache size set by user
    int cache[CACHE_SIZE];
    int n;
    for (n = 0; n < CACHE_SIZE; n++){//initialise cache array so that requests for page 0 would be valid 
         cache[n] = -1;
    }
    char cache2[1000]; //secondary cache to store input from text file
    int j = 0;//keeps track of which entry has been in the longest
    int faultno = 0;
    while (fgets(cache2,100,stdin)){//while it's still reading from the file
        int page_num = atoi(cache2);//gets the page number from the secondary cache as an int
        int i;
        for (i = 0; i < CACHE_SIZE; i++){
            if (page_num == cache[i]){//if page is in the cache, go to the next requested page
                break;
            }
            if (i == CACHE_SIZE - 1){//if iterator reaches last entry of the cache, the page is not in cache
                printf("Page %d caused a page fault.\n", page_num);//display the error
                faultno++;
                cache[j] = page_num;//inserts new page into 
                j++;
                if (j == CACHE_SIZE){//wraps around
                    j = 0;
                }
            }
        }
    }
    printf("%d Faults", faultno);
    return 0;
}