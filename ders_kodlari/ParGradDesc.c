#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "time.h"

#define MASTER 0
#define COMM MPI_COMM_WORLD

float *create1DArray( int n ) {
   float *v = (float *)malloc( n * sizeof(float) );
   return v;
}

void fillArray(float *v, int n) {
   srand( time( 0 ) );
   int i;
   for (i = 0; i < n; i++)
      v[i] = (float)(rand() % 10) / 10.0;
}

float innerProd(float *u, float * v, int n) {
   int i;
   float sum = 0.0;
   for (i = 0; i < n; i++)
      sum += u[i] * v[i];
   return sum;
}

float *matVecProd(float *M, float *v, int n1, int n2) {
   float *r = create1DArray( n1 );
   int i;
   for (i = 0; i < n1; i++)
      r[i] = innerProd(&M[i*n2], v, n2);
   return r;
}

float *vecSubt(float *u, float *v, int n) {
   float *r = create1DArray( n );
   int i;
   for (i = 0; i < n; i++)
      r[i] = u[i] - v[i];
   return r;
}

float *scalarProd(float *u, float alpha, int n) {
   float *r = create1DArray( n );
   int i;
   for (i = 0; i < n; i++)
      r[i] = alpha * u[i];
   return r;
}

int main(int *argc, char* argv[]) {

int const n1 = atoi( argv[1] );
int const n2 = atoi( argv[2] );
float const ALPHA = atof( argv[3] );
int const NITERS = atoi( argv[4] );

int rank, size;

MPI_Init(NULL, NULL);

MPI_Comm_size(COMM, &size);
MPI_Comm_rank(COMM, &rank);

int chunk1 = n1 / size;
int chunk2 = n2 / size;

float *A, *x, *b, *A_local, *b_local, *r_local, *y_local, *y, *A_local_T, *x_local, *u_local;

x = create1DArray( n2 );

if (rank == MASTER) {
   A = create1DArray( n1 * n2 );
   fillArray(A, n1 * n2);

   fillArray(x, n2);

   b = create1DArray( n1 );
   fillArray(b, n1);
}

// Row type
MPI_Datatype rowType;
MPI_Type_contiguous(n2, MPI_FLOAT, &rowType);
MPI_Type_commit(&rowType);

// Col type
MPI_Datatype colType, newColType;
MPI_Type_vector(n1, 1, n2, MPI_FLOAT, &colType);
MPI_Type_commit(&colType);

MPI_Type_create_resized(colType, 0, sizeof(float), &newColType);
MPI_Type_commit(&newColType);

int iter;
for (iter = 1; iter <= NITERS; iter++) {

// Broadcast x as initial guess vector
MPI_Bcast(x, 1, rowType, MASTER, COMM);

// Scatter A matrix
A_local = create1DArray(chunk1 * n2);
MPI_Scatter(A, chunk1, rowType, A_local, chunk1 * n2, MPI_FLOAT, MASTER, COMM);

// Scatter b vector
b_local = create1DArray(chunk1);
MPI_Scatter(b, chunk1, MPI_FLOAT, b_local, chunk1, MPI_FLOAT, MASTER, COMM);

// Compute A_local * x - b_local = y_local
y_local = create1DArray(chunk1);
r_local = create1DArray(chunk1);
r_local = matVecProd(A_local, x, chunk1, n2); // multipication
y_local = vecSubt(r_local, b_local, chunk1);  // subtraction

// Allgather y from y_local's
y = create1DArray(n1);
MPI_Allgather(y_local, chunk1, MPI_FLOAT, y, chunk1, MPI_FLOAT, COMM);

// Scatter columns of A into A_local_T's
A_local_T = create1DArray(chunk2 * n1);
MPI_Scatter(A, chunk2, newColType, A_local_T, chunk2 * n1, MPI_FLOAT, MASTER, COMM);

// Compute A_local_T * y = u_local
u_local = create1DArray( chunk2 );
u_local = matVecProd(A_local_T, y, chunk2, n1); // multipication

// Scatter x into x_local's
x_local = create1DArray( chunk2 );
MPI_Scatter(x, chunk2, MPI_FLOAT, x_local, chunk2, MPI_FLOAT, MASTER, COMM);

// Compute x_local := x_local - ALPHA * u_local
x_local = vecSubt( x_local, scalarProd(u_local, ALPHA, chunk2), chunk2 );

// Gather x_local's and obtain the solution
MPI_Gather(x_local, chunk2, MPI_FLOAT, x, chunk2, MPI_FLOAT, MASTER, COMM);

}

MPI_Finalize();

}