#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"

#define COMM MPI_COMM_WORLD

int main(void)
{

    MPI_Init(NULL, NULL);

    int rank, size;

    MPI_Comm_rank(COMM, &rank);
    MPI_Comm_size(COMM, &size);

    double value = 4;
    int step = 2; 

    int i;
    for(i = 0; i < 4; i++){


        //sola gonderenler
        if((rank % step) >= (step/2)){


            MPI_Send(&value,1, MPI_DOUBLE, rank - (step/2), 777, COMM);
            double data = 0;
            MPI_Recv(&data,1,MPI_DOUBLE,rank + (step/2), 777, COMM,MPI_STATUS_IGNORE);
            value += data;


        }else{//saga gonderenler

            double data = 0;
            MPI_Recv(&data,1,MPI_DOUBLE,rank - (step/2), 777, COMM,MPI_STATUS_IGNORE);
            MPI_Send(&value,1, MPI_DOUBLE, rank + (step/2), 777, COMM);
            value += data;

        }

        step *= 2;
    
    }


    MPI_Finalize();
}
