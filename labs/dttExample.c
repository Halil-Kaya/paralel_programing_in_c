#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define COMM MPI_COMM_WORLD
#define R 6
#define C 8

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
if ( rank == MASTER ) {
   A = (float *)malloc(sizeof(float) * R * C);
   fillArray(A, R * C);
}

float *localRow = (float *)malloc(sizeof(float) * C);
float *localCol = (float *)malloc(sizeof(float) * R);


MPI_Datatype rowType, colType, newColType, newColType2, newColType3;

// Question 1: Scatter rows of matrix A
MPI_Type_contiguous(C, MPI_FLOAT, &rowType);
MPI_Type_commit(&rowType);

MPI_Scatter(A, 1, rowType, localRow, C, MPI_FLOAT, MASTER, COMM); 

// Question 2: Scatter columns of matrix A
int count = R;
int blen = 1;
int stride = C;
MPI_Type_vector(count, blen, stride, MPI_FLOAT, &colType);
MPI_Type_commit(&colType);

MPI_Type_create_resized(colType, 0, 1*sizeof(float), &newColType);
MPI_Type_commit(&newColType);

MPI_Scatter(A, 1, newColType, localCol, R, MPI_FLOAT, MASTER, COMM);

// Question 3: Scatter even-indexed columns of matrix A
MPI_Type_create_resized(colType, 0, 2*sizeof(float), &newColType2);
MPI_Type_commit(&newColType2);

MPI_Scatter(A, 1, newColType2, localCol, R, MPI_FLOAT, MASTER, COMM);

// Question 4:
float *localCol2 = (float *)malloc(sizeof(float) * R * 2);

MPI_Type_create_resized(colType, 0, 1*sizeof(float), &newColType3);
MPI_Type_commit(&newColType3);

MPI_Scatter(A, 2, newColType3, localCol2, 2*R, MPI_FLOAT, MASTER, COMM);

if (rank == MASTER)
   printArray(localCol2, 2*R);


MPI_Finalize();

}