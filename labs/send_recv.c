#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define TAG 777
#define COMM MPI_COMM_WORLD

void printArray(int *a, int n) {
   int i;
   for (i = 0; i < n; i++)
      printf("%d ", a[i]);
   puts("");
}

int main(void) {

MPI_Init(NULL, NULL);

int rank, size;
MPI_Comm_rank(COMM, &rank);
MPI_Comm_size(COMM, &size);

MPI_Status *stat;

int i;
int *array = (int *)calloc(10, sizeof(int));

if (rank == MASTER) {
   for (i = 0; i < 10; i++)
       array[i] = i;
}

printArray(array, 10);
puts("");

// 0 1 2 3 4 5 6 7 8 9  P0
// 1 2 3                P1
// 6 7                  P2
if (rank == MASTER) {
   MPI_Send(&array[1], 3, MPI_INT, 1, TAG, COMM);
   MPI_Send(&array[6], 2, MPI_INT, 2, TAG+1, COMM);
} else if ( rank == 1)
   MPI_Recv(array, 3, MPI_INT, MASTER, TAG, COMM, stat);
else
   MPI_Recv(array, 2, MPI_INT, MASTER, TAG+1, COMM, stat);

printArray(array, 10);




MPI_Finalize();

}