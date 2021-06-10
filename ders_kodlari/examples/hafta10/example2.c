#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define COMM MPI_COMM_WORLD

int main(int *argc, char* argv[]) {

int rank, size, ringID;

MPI_Init(NULL, NULL);

MPI_Comm_size(COMM, &size);
MPI_Comm_rank(COMM, &rank);

//  0  1  2  3  4  5  6  7 

MPI_Comm ringComm;
int ndims = 1;
int dims[1] = {size};
int periods[1] = {1};
int reorder = 1;
MPI_Cart_create(COMM, ndims, dims, periods, reorder, &ringComm);

MPI_Comm_rank(ringComm, &ringID);

int coords[1];
MPI_Cart_coords(ringComm, ringID, ndims, coords);

int left, right;
MPI_Cart_shift(ringComm, 0, -1, &left, &right);

// printf("gridRank = %d, x = %d\n", ringID, coords[0]);
printf("gridRank = %d, left = %d right = %d\n", ringID, left, right);
 
MPI_Finalize();

}