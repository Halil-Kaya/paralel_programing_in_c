#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define COMM MPI_COMM_WORLD

int main(int *argc, char* argv[]) {

int rank, size, gridRank;

MPI_Init(NULL, NULL);

MPI_Comm_size(COMM, &size);
MPI_Comm_rank(COMM, &rank);

//  0  1  2  3  4   // dim 0 -> vertical
//  5  6  7  8  9   // dim 1 -> horizontal
// 10 11 12 13 14

MPI_Comm grid2D;
int dim = 2;
int ndims[2] = {3, 5};
int periods[2] = {1, 1};
int reorder = 1;
MPI_Cart_create(COMM, dim, ndims, periods, reorder, &grid2D);

MPI_Comm_rank(grid2D, &gridRank);

int coords[2];
MPI_Cart_coords(grid2D, gridRank, dim, coords);

int tempRank;

MPI_Cart_rank(grid2D, coords, &tempRank);

// printf("gridRank = %d, x = %d y = %d, tempRank = %d\n", gridRank, coords[0], coords[1], tempRank);
 
MPI_Finalize();

}