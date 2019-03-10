#include <stdio.h>
#include <stdlib.h>

int irand(int start, int end){//provides a random integer for populating the matrices, provided by TA
    int range = end - start + 1;
    return rand() % range + start;//range != rand
}

int main(){
    FILE *f = fopen("access3.txt","w");
    if (f == NULL){
        printf("Error opening file!\n");
        exit(1);
    }
    int j;
    for (j = 0; j < 10000; j++){
        int i = irand(1,1000);
        fprintf(f,"%d \n",i);
    }
    fclose(f);
    
}



