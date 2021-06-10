#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"

#define COMM MPI_COMM_WORLD

int main(void)
{

    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(COMM, &rank);
    MPI_Comm_size(COMM, &size);

    if(rank == 0){
        int var = 2;
        MPI_Send(&var,1,MPI_INT,1,100,COMM);

    }else if(rank == 7){

        int data=0;
        MPI_Recv(&data, 1, MPI_INT, rank-1, MPI_ANY_TAG, COMM, MPI_STATUS_IGNORE);
        data *= rank;
        printf("%d",data);

    }else{

        int data=0;
        MPI_Recv(&data, 1, MPI_INT, rank-1, MPI_ANY_TAG, COMM, MPI_STATUS_IGNORE);
        data *= rank;
        MPI_Send(&data,1,MPI_INT,rank + 1,100,COMM);

    }

    MPI_Finalize();
}
