#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

#define TAG 777
#define COMM MPI_COMM_WORLD

#define FEDERER 0
#define NADAL 1

double
randNum ()
{
  return rand () / (double) RAND_MAX;
}

int
main (void)
{

  MPI_Init (NULL, NULL);

  srand (time (NULL));

  int player, ball = 0;
  MPI_Comm_rank (COMM, &player);
  double r, fperc = 0.88, nperc = 0.91;

  MPI_Status *stat;

  while (1)
    {

      if (player == FEDERER)
	{

	  if (randNum () <= fperc)
	    {
	      puts ("FEDERER HITS THE BALL!");
	      ball++;
	      MPI_Send (&ball, 1, MPI_INT, NADAL, TAG, COMM);
	    }
	  else
	    {
	      printf ("%d hits\n", ball);
	      puts ("NADAL WINS!");
	      break;
	    }
	  MPI_Recv (&ball, 1, MPI_INT, NADAL, TAG, COMM, stat);
	}

      else
	{
	  MPI_Recv (&ball, 1, MPI_INT, FEDERER, TAG, COMM, stat);
	  if (randNum () <= nperc)
	    {
	      puts ("NADAL HITS THE BALL!");
	      ball++;
	      MPI_Send (&ball, 1, MPI_INT, FEDERER, TAG, COMM);
	    }
	  else
	    {
	      printf ("%d hits\n", ball);
	      puts ("FEDERER WINS!");
	      break;
	    }
	}

    }
    MPI_Finalize();
}