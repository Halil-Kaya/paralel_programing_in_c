#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"

#define COMM MPI_COMM_WORLD
#define N 1001

int main(void) 
{
    MPI_Init(NULL, NULL);

    int rank, size, i;

    MPI_Comm_rank(COMM, &rank);
    MPI_Comm_size(COMM, &size);

    int* array = (int*) calloc(N , sizeof(int));
    for(int i = 0;i<N;i++){
        *(array + i) = i;
    }

    int chunk = N / size;
    double x;
    double sum = 0.0, a;

    for (i = 0; i < chunk; i++) {
        int loca =  rank * chunk + i;
       sum += array[ rank * chunk + i ];
    }

    MPI_Reduce(&sum, &a, 1, MPI_DOUBLE, MPI_SUM, 0, COMM);

    if (rank == 0)
       printf("avg = %f\n", a/N);

    MPI_Finalize();

}