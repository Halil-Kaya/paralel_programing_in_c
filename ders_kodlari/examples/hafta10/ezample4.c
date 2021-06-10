#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define COMM MPI_COMM_WORLD

int main(int *argc, char* argv[]) {

int rank, size, cartID;

MPI_Init(NULL, NULL);

MPI_Comm_size(COMM, &size);
MPI_Comm_rank(COMM, &rank);

//  0  1  2  3  4   // dim 0 -> vertical
//  5  6  7  8  9   // dim 1 -> horizontal
// 10 11 12 13 14

MPI_Comm cart2D;
int ndims = 2;
int dims[2] = {3, 5};
int periods[2] = {1, 1};
int reorder = 1;
MPI_Cart_create(COMM, ndims, dims, periods, reorder, &cart2D);

MPI_Comm_rank(cart2D, &cartID);

int coords[2];
MPI_Cart_coords(cart2D, cartID, ndims, coords);

int left, right, up, down;
MPI_Cart_shift(cart2D, 0, 1, &up, &down);


// printf("gridRank = %d, left = %d right = %d up = %d down = %d\n", cartID, left, right, up, down);

int x = 0;
if (cartID % 5 == 0)
	x = 77;

MPI_Status stat;
MPI_Cart_shift(cart2D, 1, 1, &left, &right);
if ( cartID % 5 == 1 ) {
   // printf("rank = %d, left = %d right = %d\n", cartID, left, right); 
   // MPI_Sendrecv(&x, 1, MPI_INT, right, 333, &x, 1, MPI_INT, left, 333, cart2D, &stat);
}

if (cartID % 5 == 0)
   MPI_Send(&x, 1, MPI_INT, right+1, 777, cart2D);
else if (cartID % 5 == 2)
   MPI_Recv(&x, 1, MPI_INT, left-1, 777, cart2D, &stat);

printf("myRank = %d, my x = %d\n", cartID, x);
 
MPI_Finalize();

}