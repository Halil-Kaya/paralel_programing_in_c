#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define TAG 777
#define COMM MPI_COMM_WORLD
#define N 1000

int main(void) {

MPI_Init(NULL, NULL);

int rank, size;
MPI_Comm_rank(COMM, &rank);
MPI_Comm_size(COMM, &size);

MPI_Status *stat;
MPI_Request *req;

// Only for 2 processes
double *dizi = (double *)calloc(N, sizeof(double));
 
/* Deadlock occurence
if (rank == 0) {
   MPI_Send(dizi, N, MPI_DOUBLE, 1, TAG, COMM);
   MPI_Recv(dizi, N, MPI_DOUBLE, 1, TAG+1, COMM, stat);
} else {
   MPI_Send(dizi, N, MPI_DOUBLE, 0, TAG+1, COMM);
   MPI_Recv(dizi, N, MPI_DOUBLE, 0, TAG, COMM, stat);
}
*/

/* Deadlock solved!
if (rank == 0) {
   MPI_Send(dizi, N, MPI_DOUBLE, 1, TAG, COMM);
   MPI_Recv(dizi, N, MPI_DOUBLE, 1, TAG+1, COMM, stat);
} else {
   MPI_Recv(dizi, N, MPI_DOUBLE, 0, TAG, COMM, stat);
   MPI_Send(dizi, N, MPI_DOUBLE, 0, TAG+1, COMM);
}
*/

if (rank == 0) {
   MPI_Isend(dizi, N, MPI_DOUBLE, 1, TAG, COMM, req);
   MPI_Irecv(dizi, N, MPI_DOUBLE, 1, TAG+1, COMM, req);
} else {
   MPI_Isend(dizi, N, MPI_DOUBLE, 0, TAG+1, COMM, req);
   MPI_Irecv(dizi, N, MPI_DOUBLE, 0, TAG, COMM, req);
}

MPI_Finalize();

}