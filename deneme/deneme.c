#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"

#define COMM MPI_COMM_WORLD

int main(void)
{


    MPI_Init(NULL, NULL);

    int rank, size, i;
    MPI_Comm_rank(COMM, &rank);
    MPI_Comm_size(COMM, &size);

    printf("rank : %d size : %d\n",rank,size);
    
    if(rank == 2){

        int r1;
        //burda fikir yurutuyorum burda program asenkron calismiyor senkron olarak calisip bu satiri bekliyor
        //parametrelerin anlami;
        /*
            1.parametre -> gelen datayı nereye koyayım
            2.parametre -> count olarak geciyor sebebi: ??? 
            3.parametre -> gelen datanin turu
            4.parametre -> hangi rankin datasi
            5.parametre -> tag olarak geciyor sebebi : ???
            6.parametre -> communicator olarak geciyor sebebi : ???
            7.parametre -> MPI_Status olarak geciyor sebebi : ???

        */
        MPI_Recv(&r1, 1, MPI_INT, 1, MPI_ANY_TAG, COMM, MPI_STATUS_IGNORE);
        printf("rank1 in gonderdigi sayi: %d",r1);

    }

    if(rank == 1){

        /*
        !!NOT BURDA SAYI GONDERMIYOR ONUN ADRESINI GONDERIYOR!
        */

        int gonderilecekOlanSayi = 100;
        MPI_Send(&gonderilecekOlanSayi ,1,MPI_INT,2,100,COMM);

    }




    MPI_Finalize();
}


/*
MPI_Recv(
    void* data,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm communicator,
    MPI_Status* status)


    MPI_Send(
    void* data,
    int count,
    MPI_Datatype datatype,
    int destination,
    int tag,
    MPI_Comm communicator)

*/


//kaynak: https://mpitutorial.com/tutorials/mpi-send-and-receive/