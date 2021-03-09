#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define COMM MPI_COMM_WORLD

int main(void){

    MPI_Init(NULL,NULL);

    int size,rank;

    MPI_Comm_size(COMM,&size); //world size
    MPI_Comm_rank(COMM,&rank); // process ids

    printf("Hello world! from process %d of %d\n",rank,size);

    MPI_Finalize();

}