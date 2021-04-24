#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define COMM MPI_COMM_WORLD
#define R 10
#define C 10

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

float *A, *b;
if (rank == MASTER) {
   A = (float *)malloc(sizeof(float) * R * C);
   fillArray(A, R * C);
   // printArray(A, 30);
} else {
   b = (float *)calloc(sizeof(float), C);
}

MPI_Datatype rowType;
MPI_Type_contiguous(C, MPI_FLOAT, &rowType);
MPI_Type_commit(&rowType);

// process 0, a matrisinin 3. satirini process 1'e gondersin.
MPI_Status *stat;
if (rank == MASTER)
   MPI_Send(&A[2*R], 1, rowType, 1, 777, COMM);
   // MPI_Send(&A[2*R], C, MPI_FLOAT, 1, 777, COMM);
else
   MPI_Recv(b, C, MPI_FLOAT, MASTER, 777, COMM, stat);
   // MPI_Recv(b, 1, rowType, MASTER, 777, COMM, stat);
   

MPI_Type_free(&rowType);

MPI_Barrier(COMM);

if (rank == 1)
   printArray(b, C);

MPI_Finalize();

}