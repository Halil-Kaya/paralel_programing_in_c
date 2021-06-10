#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define COMM MPI_COMM_WORLD

int main(int *argc, char* argv[]) {

int rank, size, newRank, newSize;

MPI_Init(NULL, NULL);

MPI_Comm_size(COMM, &size);
MPI_Comm_rank(COMM, &rank);

MPI_Group fullGroup, group1, group2, newGroup;
MPI_Comm newComm;

MPI_Comm_group(COMM, &fullGroup);
int ranks1[4] = {2, 4, 5, 6};
int ranks2[5] = {0, 1, 2, 4, 7};

MPI_Group_incl(fullGroup, 4, ranks1, &group1);
MPI_Group_incl(fullGroup, 5, ranks2, &group2);

MPI_Group_intersection(group1, group2, &newGroup);
MPI_Comm_create(COMM, newGroup, &newComm);

newSize = -1; newRank = -1;
if (newComm != MPI_COMM_NULL) {
   MPI_Comm_size(newComm, &newSize);
   MPI_Comm_rank(newComm, &newRank);
}

printf("rank = %d, newRank = %d\n", rank, newRank);


MPI_Finalize();

}