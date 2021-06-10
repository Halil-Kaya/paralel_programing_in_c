#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define COMM MPI_COMM_WORLD

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

int rank, size, i, subRank, subSize;

MPI_Init(NULL, NULL);

MPI_Comm_size(COMM, &size);
MPI_Comm_rank(COMM, &rank);

MPI_Group fullGroup, colGroup1;
MPI_Comm colComm1;

MPI_Comm_group(COMM, &fullGroup);

int *r = (int *)malloc(4*sizeof(int));
for (i = 0; i < 4; i++)
   r[i] = 4 * i + 1;  // 2nd column of 4 x 4 matrix

MPI_Group_incl(fullGroup, 4, r, &colGroup1);

MPI_Comm_create(COMM, colGroup1, &colComm1);

int x = 7;

if (colComm1 != MPI_COMM_NULL) { // If i am a member of colComm1
        MPI_Comm_rank(colComm1, &subRank);
	if (subRank == 0)
   		x = 77;
	MPI_Bcast(&x, 1, MPI_INT, 0, colComm1);
        printf("rank = %d, subRank = %d, x = %d\n", rank, subRank, x);
}

MPI_Finalize();

}