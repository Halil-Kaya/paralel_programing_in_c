#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"

#define COMM MPI_COMM_WORLD
#define N 100
#define PI acos(-1)

double f(double x) { return 4 / (1 + x * x ); } 

double appPI = 0.0;

int main(void) {

MPI_Init(NULL, NULL);

int rank, size, i;
MPI_Comm_rank(COMM, &rank);
MPI_Comm_size(COMM, &size);

int chunk = N / size;
double x;
double sum = 0.0;
for (i = 0; i < chunk; i++) {
   x = ( rank * chunk + i ) / (double)N ;
   sum += f( x );
}
sum /= N;

printf("Rank %d: %f\n", rank, sum);

appPI += sum;
if (rank == 0)
   printf("Approx PI = %f\n", appPI);

return 0;

MPI_Finalize();

}


