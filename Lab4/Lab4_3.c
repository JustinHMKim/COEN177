/*
 * #Name: Justin Kim
 *
 *# Date: 1/29/19 Tuesday labs
 *
 *# Title: Lab4 - Step 3
 *
 *
 * Description: This program uses threads to perform a parallel matrix multiply
 *
 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <pthread.h>
#define SIZE 1024
void matrixMultiply();
void printMatrix(float mt[SIZE][SIZE]);

pthread_t threads[SIZE];

float a[SIZE][SIZE], b[SIZE][SIZE], c[SIZE][SIZE], d[SIZE][SIZE]; //declares the matrices 

void *mthmatrixMultiply(void *arg){//for the multi-threaded multiplication
     int x = (int)arg;
     int i,j;
     for (i = 0; i < SIZE; i++)
         for (j = 0; j < SIZE; j++)
             c[i][x] += a[i][j] * b[j][x];//calculates each column 
}

bool is_result_correct(){//checks the single and multi-threaded matrix multiplication outputs against each other
    int i, j; 
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            if (c[i][j] != d[i][j]){
                printf("%.1f \n", c[i][j]);//allows for checking which initial value resulted in a mismatch in order to isolate the error
                return false;
            }
    return true; 
}



int irand(int start, int end){//provides a random integer for populating the matrices, provided by TA
    int range = end - start + 1;
    return rand() % range + start;//range != rand
}


int main(){
int m,n; 

    for (m = 0; m < SIZE; m++){
        for (n = 0; n < SIZE; n++){//populates the matrices with random integers
            a[m][n] = irand(0,5);
            b[m][n] = irand(0,5);
        } 
    }
    printMatrix(a);//for checking if the matrix was populated correctly
    matrixMultiply();//single-threaded multiplication 
    printf("Singlethreaded Approach : \n");
    printMatrix(d);//checking the results of the single-threaded multiplication.
    int p;
    for (p = 0; p < SIZE/2; p++)//launches the first half of the threads for the multi-threaded multiplication
        pthread_create(&threads[p], NULL, mthmatrixMultiply, (void *)p);//launches a thread for each column
    for (p = 0; p < SIZE/2; p++){
        pthread_join(threads[p],NULL);//waits until each thread has finished before terminating, makes sure every column has been filled
    }
    for (p = SIZE/2; p < SIZE; p++)//launches the second half of the threads for the multi-threaded multiplication
        pthread_create(&threads[p],NULL,mthmatrixMultiply, (void *)p);
    for (p = SIZE/2; p < SIZE; p++)
        pthread_join(threads[p],NULL);
    printf("Multi-threaded Approach : \n");
    printMatrix(c);//checking the results of the multi-threaded multiplication
    if (is_result_correct() == true )
       printf("True \n");
    else
       printf("False \n");
}

void matrixMultiply() {//single-threaded multiplication, code provided in assignment
    unsigned i,j,k;
    for ( i = 0; i < SIZE; i ++)
        for ( j = 0; j < SIZE; j ++)
            for ( k = 0; k < SIZE; k++)
                d [ i][ j ] += a[ i][ k ] * b [ k][ j];
}

void printMatrix(float mt[SIZE][SIZE]){//prints out matrix for checking results
     size_t z, y;
     for ( z = 0; z < SIZE; z++){
         for ( y = 0; y < SIZE ; y++){
             printf("%.1f ", mt[z][y]);
         }
     printf("\n");
     }
}
