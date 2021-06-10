#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define COMM MPI_COMM_WORLD

int main(int *argc, char* argv[]) {

int rank, size, newRank, newSize;

MPI_Init(NULL, NULL);

MPI_Comm_size(COMM, &size);
MPI_Comm_rank(COMM, &rank);

MPI_Comm newComm;

int color[7] = {0, 1, 1, 2, 0, 2, 2};
MPI_Comm_split(COMM, color[rank], rank, &newComm); // 3 disjoint communicators constructed

MPI_Comm_size(newComm, &newSize);
MPI_Comm_rank(newComm, &newRank);

MPI_Status stat;

int x = 5;
if (newRank == 0) {
   x = 55;
   MPI_Send(&x, 1, MPI_INT, 1, 777, newComm);
} 
else if (newRank == 1)
   MPI_Recv(&x, 1, MPI_INT, 0, 777, newComm, &stat);

printf("%d of %d --> %d of %d x = %d\n", rank, size-1, newRank, newSize-1, x);

MPI_Finalize();

}