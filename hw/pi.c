#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"

#define COMM MPI_COMM_WORLD
#define N 200
#define PI acos(-1)

double f(double x) { return 4 / (1 + x * x); }

double appPI = 0.0;

int main(void)
{

    MPI_Status status;

    MPI_Init(NULL, NULL);

    int rank, size, i;
    MPI_Comm_rank(COMM, &rank);
    MPI_Comm_size(COMM, &size);

    int chunk = N / size;
    double x;
    double sum = 0.0;
    for (i = 0; i < chunk; i++)
    {
        x = (rank * chunk + i) / (double)N;
        sum += f(x);
    }
    sum /= N;

        

    printf(" pi sum: %1.10f\n",sum);

    if(rank != 0){

        MPI_Send(&sum,1,MPI_DOUBLE,0,100,COMM);

    }else{

        double r1,r2,r3;
        MPI_Recv(&r1, 1, MPI_DOUBLE, 1, MPI_ANY_TAG, COMM, MPI_STATUS_IGNORE);
        MPI_Recv(&r2, 1, MPI_DOUBLE, 2, MPI_ANY_TAG, COMM, MPI_STATUS_IGNORE);
        MPI_Recv(&r3, 1, MPI_DOUBLE, 3, MPI_ANY_TAG, COMM, MPI_STATUS_IGNORE);
        double resultSum = sum + r1 + r2 + r3;
        printf("Gercek Pi : %1.10f\n",PI);
        printf("Yaklasik Pi : %1.10f\n",resultSum);

    }


    MPI_Finalize();
}
