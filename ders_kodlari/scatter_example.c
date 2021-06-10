#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"

#define COMM MPI_COMM_WORLD
#define N 16
#define MASTER 5

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

int *localDizi = (int *)malloc( N/size * sizeof(int) );

MPI_Scatter(dizi, N/size, MPI_INT, localDizi, N/size, MPI_INT, MASTER, COMM);

if (rank == 5)
   printArray(localDizi, 2);


MPI_Finalize();

}