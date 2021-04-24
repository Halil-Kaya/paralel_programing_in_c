#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define COMM MPI_COMM_WORLD
// #define R 8
// #define C 5

float innerProd(float *a, float *b, int n) {
   int i;
   float sum = 0.0;
   for (i = 0; i < n; i++)
      sum += a[i] * b[i];

   return sum;
}

float* multiply(float *A, float *x, int r, int c) {
   int i;
   float *result = (float *)malloc( sizeof(float) * r);
   for (i = 0; i < r; i++)
      result[i] = innerProd( &A[i * c], x, c );
      
   return result;
}

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

int R = atoi( argv[1] );
int C = atoi( argv[2] );

int rank, size, chunk;

MPI_Init(NULL, NULL);

MPI_Comm_size(COMM, &size);
MPI_Comm_rank(COMM, &rank);

chunk = R / size;  // number of rows for each process

float *A;  // matrix
float *x;  // vector
float *b;  // result vector

float *A_local;  // local matrices
float *b_local;  // local result vectors

x = (float *)malloc( sizeof(float) * C);
if ( rank == MASTER) {
   A = (float *)malloc( sizeof(float) * R * C );

   fillArray(A, R * C);
   fillArray(x, C);

   b = (float *)malloc( sizeof(float) * R );
}

// Scatter A matrix to each process
A_local = (float *)malloc( sizeof(float) * chunk * C);
MPI_Scatter(A, chunk * C, MPI_FLOAT, A_local, chunk * C, MPI_FLOAT, MASTER, COMM);

// Broadcast x to COMM
MPI_Bcast(x, C, MPI_FLOAT, MASTER, COMM);

// Local computation
b_local = (float *)malloc( sizeof(float) * chunk);
b_local = multiply(A_local, x, chunk, C);

// Gather b_locals into MASTERS' b
MPI_Gather(b_local, chunk, MPI_FLOAT, b, chunk, MPI_FLOAT, MASTER, COMM);

if (rank == MASTER)
   printArray(b_local, chunk);


MPI_Finalize();

}