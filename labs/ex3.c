#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define COMM MPI_COMM_WORLD
#define N 4

void fillArray(float *A, int k) {
   int i;
   for (i = 0; i < k; i++)
      A[i] = (float)i+1.0;
}

void printArray(float *xx, int n) {
   int i;
   for (i = 0; i < n; i++)
      printf("%.1f\t", xx[i]);
   puts("");
}

int main(int *argc, char* argv[]) {

int rank, size;

MPI_Init(NULL, NULL);

MPI_Comm_size(COMM, &size);
MPI_Comm_rank(COMM, &rank);

float *A; 
float x = 0.0;
if ( rank == MASTER ) {
   A = (float *)malloc(sizeof(float) * N * N);
   fillArray(A, N * N);
}

MPI_Datatype diagType;
int count, blen, stride;
count = N;
blen = 1;
stride = N+1;
MPI_Type_vector(count, blen, stride, MPI_FLOAT, &diagType);
MPI_Type_commit(&diagType);

MPI_Status stat;
float b[4] = {0};
if (rank == 0)
   MPI_Send(A, 1, diagType, 1, 777, COMM);

if (rank == 1)
   MPI_Recv(b, 4, MPI_FLOAT, 0, 777, COMM, &stat);

if (rank == 1)
   printArray(b, 4);

// MPI_Scatter(A, 1, diagType, &x, 4, MPI_FLOAT, MASTER, COMM);

printf("my rank = %d\t my x = %f\n", rank, x);

MPI_Type_free(&diagType);

MPI_Barrier(COMM);


MPI_Finalize();

}