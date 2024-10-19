#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>



int main (int argc, char *argv[])
{
    MPI_Init (&argc, &argv);
    int rank, commsize;
    double end_time;
    double start_time;
    MPI_Comm_size (MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    int COUNT = 1024;
    if(rank == 0)
        printf("Commsize: %d\n", commsize);
    FILE *file = NULL;
    if (rank == 0) {
        file = fopen("result_4node_4proc.txt", "w");
        if (file == NULL) {
            printf("Ошибка открытия файла!\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    for(int i = 0; i <= 1; i++)
    {
        char *sbuf = (char*)malloc(COUNT * sizeof(char));
        char *rbuf = (char*)malloc(COUNT * sizeof(char));
        if (sbuf == NULL || rbuf == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        for(int b = 0; b < COUNT; b++)
        {
            sbuf[b] = rand() % 128;
        }
        if (rank == 0)
            start_time = MPI_Wtime ();
        if(rank == 0)
        {
            for(int j = 1; j < commsize; j++)
            {
                MPI_Send (sbuf, COUNT, MPI_CHAR, j, 0, MPI_COMM_WORLD);
                printf("Process %d sent message to %d \n", rank, j);
            }
        }
        else
        {
            MPI_Recv (rbuf, COUNT, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process %d received message from %d\n", rank, 0);
        }
        MPI_Barrier(MPI_COMM_WORLD);
        

        if (rank == 0)
        {
            end_time = MPI_Wtime ();
            //fprintf(file, "%d %lf\n", 
                   //COUNT, end_time - start_time);
            printf("%d %lf\n", 
                   COUNT, end_time - start_time);
        }
            
        COUNT *= 1024;
        free(rbuf);
        free(sbuf);
    }
    MPI_Finalize();
    return 0;
}