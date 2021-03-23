#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"

#define COMM MPI_COMM_WORLD

void myReduce(int rank, int size,int *sayi)
{

    myReduceRecursive(rank,size,sayi,1);

}

void myReduceRecursive(int rank, int size,int *sayi,int q){


    int rankCheck = 0;

    for (int i = size - q; i >= 0; i -= q*2){
        if (rank == i){
            
            rankCheck = 1;
            break;
        }
    }

    if (rankCheck){

        if(rank - q < 0){
            //islem artik bitebilir
            return;
        }

        MPI_Send(sayi, 1, MPI_INT, rank - q, 100, COMM);
        printf("<%d>ranki : %d olan ranki %d olana data gonderiyor\n",q,rank,rank-q);
    }
    else{

        int data = 0;
        MPI_Recv(&data, 1, MPI_INT, rank + q, MPI_ANY_TAG, COMM, MPI_STATUS_IGNORE);
        printf("<%d>ranki : %d olan ranki %d olandan data aliyor data: %d \n",q,rank,rank+q,data);
        *sayi += data;

        myReduceRecursive(rank,size,sayi,2*q);

    }

}

int main(void)
{

    int count = 3;

    MPI_Init(NULL, NULL);

    int rank, size, i;

    MPI_Comm_rank(COMM, &rank);
    MPI_Comm_size(COMM, &size);

    int sayi = 4;

    myReduce(rank,size,&sayi);

    if(rank == 0){
        printf("sonuc:: %d",sayi);
    }


    MPI_Finalize();
}
