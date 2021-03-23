#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"

#define COMM MPI_COMM_WORLD

/*
    if(rank != 0){
      
        MPI_Send(&rank,1,MPI_INT,0,100,COMM);

    }else{

        for(int i = 1 ; i < size;i++){
            int rData = 0;
            MPI_Recv(&rData, 1, MPI_INT, i, MPI_ANY_TAG, COMM, MPI_STATUS_IGNORE);
            printf("rank %d a gelen %d \n",rank,rData);
        }
        
    }

*/

void myReduce(int *result, int rank, int size)
{

    printf("rank: %d size: %d \n", rank, size);
}
int main(void)
{

    int count = 3;

    MPI_Init(NULL, NULL);

    int rank, size, i;

    MPI_Comm_rank(COMM, &rank);
    MPI_Comm_size(COMM, &size);

    int sayi = 4;

    int rankCheck = 0;

    for (int i = size - 1; i >= 0; i -= 2){
        if (rank == i){
            
            rankCheck = 1;
            break;
        }
    }


    if (rankCheck){

        MPI_Send(&sayi, 1, MPI_INT, rank - 1, 100, COMM);
        printf("<1>ranki : %d olan ranki %d olana data gonderiyor\n",rank,rank-1);
    }
    else{
        int data = 0;
        MPI_Recv(&data, 1, MPI_INT, rank + 1, MPI_ANY_TAG, COMM, MPI_STATUS_IGNORE);
        printf("<1>ranki : %d olan ranki %d olandan data aliyor data: %d \n",rank,rank+1,data);
        sayi += data;


        for (int i = size - 2; i >= 0; i -= 4){
            if (rank == i){
                
                rankCheck = 1;
                break;
            }
        }

        if (rankCheck){

            MPI_Send(&sayi, 1, MPI_INT, rank - 2, 100, COMM);
            printf("<2>ranki : %d olan ranki %d olana data gonderiyor\n",rank,rank-2);
        }
        else{
            int data = 0;
            MPI_Recv(&data, 1, MPI_INT, rank + 2, MPI_ANY_TAG, COMM, MPI_STATUS_IGNORE);
            printf("<2>ranki : %d olan ranki %d olandan data aliyor data: %d \n",rank,rank+2,data);
            sayi += data;


            for (int i = size - 4; i >= 0; i -= 8){
                if (rank == i){
                    
                    rankCheck = 1;
                    break;
                }
            }

            if (rankCheck){

                MPI_Send(&sayi, 1, MPI_INT, rank - 4, 100, COMM);
                printf("<3>ranki : %d olan ranki %d olana data gonderiyor\n",rank,rank-4);
            }
            else{
                int data = 0;
                MPI_Recv(&data, 1, MPI_INT, rank + 4, MPI_ANY_TAG, COMM, MPI_STATUS_IGNORE);
                printf("<3>ranki : %d olan ranki %d olandan data aliyor data: %d \n",rank,rank+4,data);
                sayi += data;

                for (int i = size - 8; i >= 0; i -= 16){
                    if (rank == i){
                        
                        rankCheck = 1;
                        break;
                    }
                }

                if(rank -8 < 0){
                    printf("<5>sonuc: %d",sayi);
                }


                
            }


        }




    }


    MPI_Finalize();
}
