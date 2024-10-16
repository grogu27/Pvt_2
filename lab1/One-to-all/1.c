#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>



int main (int argc, char *argv[])
{
    MPI_Init (&argc, &argv);
    int rank, commsize;
    MPI_Comm_size (MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    int n = 1024;

    FILE *file = NULL;
    if (rank == 0) {
        file = fopen("result.txt", "w");
        if (file == NULL) {
            printf("Ошибка открытия файла!\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    for(int i = 0; i <= 1; i++)
    {
        char *sbuf = (char*)malloc(n * sizeof(char));
        char *rbuf = (char*)malloc(n * sizeof(char));
        if (sbuf == NULL || rbuf == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        for(int b = 0; b < n; b++)
        {
            sbuf[b] = rand() % 128;
        }
        double start_time = MPI_Wtime ();
        if(rank == 0)
        {
            for(int j = 1; j < commsize; j++)
            {
                MPI_Send (sbuf, n, MPI_CHAR, j, 0, MPI_COMM_WORLD);
                printf("Process %d sent message to %d \n", rank, j);
            }
        }
        else
        {
            MPI_Recv (rbuf, n, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process %d received message from %d\n", rank, 0);
        }
        double end_time = MPI_Wtime ();

        if (rank == 0)
        {
            fprintf(file, "Message size: %d, Time = %lf\n", 
                   n, end_time - start_time);
            // printf("Message size: %d, Time = %lf\n", 
            //        COUNT, end_time - start_time);
        }
            
        n *= 1024;
        free(rbuf);
        free(sbuf);
    }
    MPI_Finalize();
    return 0;
}