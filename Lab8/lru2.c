/*
 * *#Name: Justin Kim
 * *# Date: 2/26/19 Tuesday labs
 * *# Title: Lab 8 LRU
 * * Description: This program implements the least recently used algorithm 
* */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {//to 
    int pageno;
    int count;
} ref_page;

int main(int argc, char *argv[]){
    int CACHE_SIZE = atoi(argv[1]);//set by user
    int faultno = 0;
    ref_page cache[CACHE_SIZE];
    int n;
    for (n = 0; n < CACHE_SIZE; n++){//initialise the cache array, pageno set to allow for page 0 to be entered properly, count set where the higher the number, the less recently the entry has been used
        cache[n].pageno = -1;
        cache[n].count = 100;
    }
    char cache2[1000]; //secondary cache to store input from text file
    int j = 0;
    
    while (fgets(cache2,100,stdin)){//while it's still reading from the file
        int page_num = atoi(cache2);//gets the page number from the secondary cache as an int
        //printf("Requested Page: %d \n", page_num);
        int i;
        for (i = 0; i < CACHE_SIZE; i++){
            int least_rec = cache[i].count;//to start looking for the least recently used entry
            int least_pos = 0;
            if (page_num == cache[i].pageno){//if page is in the cache, go search for the next requested page
                int m;
                for (m = 0; m < CACHE_SIZE; m++){//pushes every entry more recent than the current one up by one so they become less recently used, less recent entries are unaffected
                    if (cache[m].count<cache[i].count){
                        cache[m].count = cache[m].count + 1;
                    }
                }
                cache[i].count = 0;//makes the current entry the most recently used
                break;
            }

            if (i == CACHE_SIZE - 1){//if iterator reaches last entry of the cache, the page is not in cache
                int t;
                for (t = 0; t < CACHE_SIZE; t++){//pushes every entry up as none are the most recent one any more
                    cache[t].count = cache[t].count + 1;    
                }    
                int k;
                for (k = 0; k < CACHE_SIZE; k++){//finds the least recently used entry
                    if (least_rec < cache[k].count){
                        least_rec = cache[k].count;
                        least_pos = k;
                    }
                }
                printf("Page %d caused a page fault.\n", page_num);//display the error
                faultno++;
                cache[least_pos].pageno = page_num;//inserts new page into the least recently used position in the cache
                cache[least_pos].count = 0;//sets it to the most recent
                j++;
                if (j == CACHE_SIZE - 1){//wraps around
                    j = 0;
                }
            }
        }    
    }
    printf("%d Faults", faultno);
    return 0;
}