#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const double PI = 3.14159265358979323846;
int n = 10000000;
double getrand()
{ 
    return (double)rand() / RAND_MAX; 
}
double func(double x, double y)
{ 
    return exp(x - y); 
}
int main(int argc, char **argv)
{
  
    MPI_Init(&argc, &argv);
    double start_time;
    double end_time;
    int rank, commsize;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    int in = 0;
    int gin = 0;
    double s = 0;
    double gsum = 0.0;
    srand(time(NULL) + rank);
    start_time = MPI_Wtime();
    for(int j = 0; j < 2; j++)
    {
        for (int i = rank; i < n; i += commsize) 
        {
            double x = -1 + getrand(); /* x in [-1;0] */
            double y = getrand(); /* y in [0;1] */
           
          
                in++;
                s += func(x, y);
            
        }
        
        gin = 0;
        MPI_Reduce(&in, &gin, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        gsum = 0.0;
        MPI_Reduce(&s, &gsum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        end_time = MPI_Wtime();

        printf("Proc: %d, S: %lf\n", rank, s);

        if (rank == 0) 
        {
            double v = PI * gin / n;
            double res = v * gsum / gin;
            printf("Result: %.12f, n: %d\n", res, n);
            printf("Time: %lf\n", end_time - start_time);
            printf("gin: %d\n", gin);
        }
        n *= 10;
    }

    MPI_Finalize();
    return 0;
}