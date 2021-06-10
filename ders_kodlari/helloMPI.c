#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define COMM MPI_COMM_WORLD

int main(void) {

MPI_Init(NULL, NULL);  // starts parallel environment

int size, rank;

MPI_Comm_size(COMM, &size); // world size (number of procs)
MPI_Comm_rank(COMM, &rank); // process ids

if (rank % 2 == 0)
	printf("Hello world! from process %d of %d\n", rank, size);
else
        printf("Goodbye! from process %d of %d\n", rank, size);


MPI_Finalize();  // finalizes parallel environment

}