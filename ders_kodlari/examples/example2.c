#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define COMM MPI_COMM_WORLD
#define R 5
#define C 5
#define N 5

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

float *A, *b, *c, *d;
if (rank == MASTER) {
   A = (float *)malloc(sizeof(float) * R * C);
   fillArray(A, R * C);
} else {
   b = (float *)calloc(sizeof(float), N/2+1);
   c = (float *)calloc(sizeof(float), R);
   d = (float *)calloc(sizeof(float), N);
}

int count, blen, stride;
MPI_Datatype type, colType, diagType;
count = (int)N/2+1;
blen = 1;
stride = 2;
MPI_Type_vector(count, blen, stride, MPI_FLOAT, &type);
///////////////////////////////////////////////////////
count = R;
blen = 1;
stride = C;
MPI_Type_vector(count, blen, stride, MPI_FLOAT, &colType);
///////////////////////////////////////////////////////
count = N;
blen = 1;
stride = N+1;
MPI_Type_vector(count, blen, stride, MPI_FLOAT, &diagType);
///////////////////////////////////////////////////////
MPI_Type_commit(&type);
MPI_Type_commit(&colType);
MPI_Type_commit(&diagType);

MPI_Status *stat;
if (rank == MASTER) {
   MPI_Send(A, 1, type, 1, 777, COMM);
   MPI_Send(&A[3], 1, colType, 1, 778, COMM);
   MPI_Send(A, 1, diagType, 1, 779, COMM);

} else {
   MPI_Recv(b, N/2+1, MPI_FLOAT, MASTER, 777, COMM, stat);
   MPI_Recv(c, R, MPI_FLOAT, MASTER, 778, COMM, stat);
   MPI_Recv(d, N, MPI_FLOAT, MASTER, 779, COMM, stat);
}

MPI_Type_free(&type);
MPI_Type_free(&colType);
MPI_Type_free(&diagType);

MPI_Barrier(COMM);

if (rank == 1) {
   printArray(b, N/2+1);
   printArray(c, R);
   printArray(d, N);
}
MPI_Finalize();

}