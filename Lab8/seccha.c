/*
 * *#Name: Justin Kim
 * *# Date: 2/26/19 Tuesday labs
 * *# Title: Lab 8 Second Chance
 * * Description: This program implements the Second Chance algorithm 
* */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {//to hold both the page and its reference bit
    int pageno;
    int refed;
} ref_page;

int main(int argc, char *argv[]){
    int CACHE_SIZE = atoi(argv[1]);//Cache size set by user
    int faultno = 0;
    int notfound = 0;
    ref_page cache[CACHE_SIZE];
    int n;
    for (n = 0; n < CACHE_SIZE; n++){//initialise page number to allow for page 0 to be entered properly
        cache[n].pageno = -1;
        cache[n].refed = 0;
    }
    char cache2[1000]; //secondary cache to store input from text file
    int k = 0;//tracks which entry in cache to replace
    while (fgets(cache2,100,stdin)){//while it's still reading from the file
        int page_num = atoi(cache2);//gets the page number from the secondary cache as an int
        int i;
        for (i = 0; i < CACHE_SIZE; i++){
            if (page_num == cache[i].pageno){//if page is in the cache, go to the next requested page
                cache[i].refed = 1;//set the reference bit to 0 and search for the next requested page
                notfound = 0;
                break;
            }
            if (i == CACHE_SIZE - 1){//if i hits the last entry without matching, proceed to next for loop to deal with the page fault
                notfound = 1;
            }
        }
        if (notfound == 1){    
            int j;
            for (j = k ; j < CACHE_SIZE; j++){//goes back over the whole cache
                if (cache[j].refed == 1){//if reference bit is 1, set to 0 and skip over as part of the second chance
                    cache[j].refed = 0;
                    k++;
                    if (k == CACHE_SIZE){//to wrap around if the last entry gets a second chance
                        k = 0;
                        j = -1;//because j iterates on the end of the current loop so j needs to be -1 to go back 0 instead of 0 because then j would start at 1 when searching for the next page
                    }
                }
                else{
                    cache[j].pageno = page_num;//inserts new page into the cache
                    cache[j].refed = 0;
                    faultno++;
                    printf("Page %d caused a page fault.\n", page_num);//display the error
                    k++;
                    if (k == CACHE_SIZE){//wraps around
                        k = 0;
                    }
                    break;
                }

            }
        }
    }
    printf("%d Faults", faultno);
    return 0;
}