#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define COMM MPI_COMM_WORLD
#define N 8
#define N2 (N)*(N)

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
float *v;
if ( rank == MASTER ) {
   A = (float *)malloc(sizeof(float) * N2);
   fillArray(A, N2);
} else
   v = (float *)malloc(sizeof(float) * 8);

/*
MPI_Datatype subType;

int ndims = 2;
int sizes[2] = {8, 8};
int subsizes[2] = {4, 2};
int starts[2] = {2, 4};
MPI_Type_create_subarray(ndims, sizes, subsizes, starts, MPI_ORDER_C, MPI_FLOAT, &subType);
MPI_Type_commit(&subType);

MPI_Status stat;
if (rank == MASTER)
   MPI_Send(A, 1, subType, 1, 777, COMM);
else
   MPI_Recv(v, 8, MPI_FLOAT, MASTER, 777, COMM, &stat);
*/

MPI_Datatype vType;
int count = 4, blen = 2, stride = 8;
MPI_Type_vector(count, blen, stride, MPI_FLOAT, &vType);
MPI_Type_commit(&vType);

MPI_Status stat;
if (rank == MASTER)
   MPI_Send(&A[20], 1, vType, 1, 777, COMM);
else
   MPI_Recv(v, 8, MPI_FLOAT, MASTER, 777, COMM, &stat);


if (rank == 1)
   printArray(v, 8);

MPI_Finalize();

}