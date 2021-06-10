#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define COMM MPI_COMM_WORLD

int main(void) {

MPI_Init(NULL, NULL);  // starts parallel environment

int rank, size, i;
MPI_Comm_rank(COMM, &rank);
MPI_Comm_size(COMM, &size);

int *dizi = (int *)malloc(20 * sizeof(int));
for (i = 0; i <= 20; i++)
   dizi[i] = i + 1;

int chunk = 20 / size;

printf("processor %d printing\n", rank);
for (i = 0; i < chunk; i++)
   printf("%d  ", dizi[ rank * chunk + i ]);
puts("");


MPI_Finalize();

}


