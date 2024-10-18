#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int rank, commsize;
    double start_time;
    double end_time;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int n = 1024; 
    int msg_tag = rank;
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

    for (int i = 0; i <= 1; i++) {
        size_t size_rbuf = (commsize - 1) * n; 
        char *sbuf = (char*)malloc(n * sizeof(char));
        char *rbuf = (char*)malloc(size_rbuf * sizeof(char));

        if (sbuf == NULL || rbuf == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        for (int b = 0; b < n; b++) {
            sbuf[b] = rand() % 128; 
        }
        if (rank == 0)
            start_time = MPI_Wtime();
        
        if (rank != 0) {
            MPI_Send(sbuf, n, MPI_CHAR, 0, msg_tag, MPI_COMM_WORLD);
            printf("Process %d sent message to %d \n", rank, 0);
        } else {
            for (int i = 1; i < commsize; i++) {
                MPI_Recv(rbuf + (i - 1) * n, n, MPI_CHAR, i, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Process %d received message from %d\n", rank, i);
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
        

        if (rank == 0) {
            end_time = MPI_Wtime();
            fprintf(file, "%d %lf\n", 
                   n, end_time - start_time);
            printf("Message size: %d, Time = %lf\n", 
                   n, end_time - start_time);
        }
            
        n *= 1024;
        free(rbuf);
        free(sbuf);
    }
    
    if (rank == 0) {
        fclose(file); 
    }

    MPI_Finalize();
    return 0;
}
