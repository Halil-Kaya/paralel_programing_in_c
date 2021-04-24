#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define COMM MPI_COMM_WORLD
int main(void)
{
    MPI_Init(NULL, NULL);
    int rank, size, i;
    MPI_Comm_rank(COMM, &rank);
    MPI_Comm_size(COMM, &size);
    while (1)
    {
        printf("etmez");
    }
    MPI_Finalize();
    return 0;
}
