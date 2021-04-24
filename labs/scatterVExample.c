#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"

#define COMM MPI_COMM_WORLD
#define N 16
#define MASTER 0

void printArray(int *d, int n) {
int i;
for (i = 0; i < n; i++)
   printf("%d\t", d[i]);
puts("");
}


int main(void) {

MPI_Init(NULL, NULL);

int size, rank, i;

MPI_Comm_size(COMM, &size);
MPI_Comm_rank(COMM, &rank);

int *dizi;
if (rank == MASTER) {
   dizi = (int *)malloc(N * sizeof(int));
   for (i = 0; i < N; i++)
      dizi[i] = i+1;
}

const int sendCounts[4] = {5, 3, 2, 3};
const int displs[4] = {0, 5, 9, 13};

int *localDizi = (int *)malloc( sizeof(int) * sendCounts[rank] );

MPI_Scatterv(dizi, sendCounts, displs, MPI_INT, localDizi, sendCounts[rank], MPI_INT, MASTER, COMM);

if (rank == 3)
   printArray(localDizi, sendCounts[rank]);

MPI_Finalize();

}