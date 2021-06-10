#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"

#define COMM MPI_COMM_WORLD
#define N 20
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

int chunkSize = N / size;
int *localDizi = (int *)malloc( N/size * sizeof(int) );

MPI_Scatter(dizi, chunkSize, MPI_INT, localDizi, chunkSize, MPI_INT, MASTER, COMM);

int localToplam = 0;
for (i = 0; i < chunkSize; i++)
   localToplam += localDizi[i];

// MPI_Barrier(COMM);
// printf("rank = %d: localToplam = %d\n", rank, localToplam);

int globalToplam = 0;
MPI_Reduce(&localToplam, &globalToplam, 1, MPI_INT, MPI_SUM, MASTER, COMM);

if (rank == MASTER)
	printf("Toplam = %d\n", globalToplam);

MPI_Finalize();

}