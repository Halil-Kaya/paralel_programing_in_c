#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"

#define COMM MPI_COMM_WORLD
#define N 10
#define MASTER 0

void printArray(int *d) {
int i;
for (i = 0; i < N; i++)
   printf("%d\t", d[i]);
puts("");
}


int main(void) {

MPI_Init(NULL, NULL);

int size, rank, i;

MPI_Comm_size(COMM, &size);
MPI_Comm_rank(COMM, &rank);

int *dizi = (int *)malloc(N * sizeof(N));
if (rank == MASTER)
   for (i = 0; i < N; i++)
      dizi[i] = i+1;
else
   for (i = 0; i < N; i++)
      dizi[i] = 0;

if (rank == MASTER)
   printArray(dizi);

MPI_Barrier(COMM);

if (rank == 7)
   printArray(dizi);

MPI_Bcast(dizi, N, MPI_INT, MASTER, COMM);

if (rank == 4)
   printArray(dizi);


MPI_Finalize();

}