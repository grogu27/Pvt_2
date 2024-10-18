#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int commsize, rank;
    int msg_tag;
    double start_time;
    double end_time;
    int COUNT = 1;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0)
        printf("Commsize: %d\n", commsize);
    FILE *file = NULL;
    if (rank == 0) {
        file = fopen("result.txt", "w");
        if (file == NULL) {
            printf("Ошибка открытия файла!\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }
    
    for (int i = 0; i < 3; i++)
    {
        char *msg = (char*)malloc(COUNT * sizeof(char));
        if (msg == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        for (int j = 0; j < COUNT; j++) 
        {
            msg[j] = rand() % 128;
        }
        msg_tag = rank;
        if (rank == 0)
            start_time = MPI_Wtime();
        // for(int k = 0; k < commsize ; k++) 
        // {
            int dest = (rank + 1) % commsize;
            int srs = (rank - 1 + commsize) % commsize;

            MPI_Sendrecv(msg, COUNT, MPI_CHAR, dest, msg_tag, 
            msg, COUNT, MPI_CHAR, srs, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process %d sent message to %d and received from %d\n", rank, dest, srs);

        //}
        MPI_Barrier(MPI_COMM_WORLD);
        

        if (rank == 0)
        {
            end_time = MPI_Wtime(); 
            fprintf(file, "%d %lf\n", 
                   COUNT, end_time - start_time);
            printf("Message size: %d, Time = %lf\n", 
                   COUNT, end_time - start_time);
        }
        COUNT *= 1024;
        free(msg);
        
        
            
    }
    if (rank == 0)
        fclose(file);
    MPI_Finalize();
    return 0;
}

