#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define COMM MPI_COMM_WORLD

int main(void){

    MPI_Init(NULL,NULL);

    int size,rank;

    MPI_Comm_size(COMM,&size); //world size
    MPI_Comm_rank(COMM,&rank); // process ids

    int *dizi = (int*)malloc(20*sizeof(int));
    int i;
    for(i = 0,i <=20; i++){
        dizi[i] = i + 1;
    }
    int sum = 0;
    #pragma omp parallel for reduction (+:sum)
    for (i=0;i<n;i++)
        sum=sum+dizi[i];


    MPI_Finalize();

}