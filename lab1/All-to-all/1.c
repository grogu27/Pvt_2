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
    if(rank == 0)
        printf("Commsize: %d\n", commsize);
    FILE *file = NULL;
    if (rank == 0) {
        file = fopen("result_2node_8proc.txt", "w");
        if (file == NULL) {
            printf("Ошибка открытия файла!\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }
    for (int i = 0; i <= 1; i++) {
        char *sbuf = (char*)malloc(n * sizeof(char));
        char *rbuf = (char*)malloc(n * commsize * sizeof(char)); 

        if (sbuf == NULL || rbuf == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        for (int b = 0; b < n; b++) {
            sbuf[b] = rand() % 128; 
        }

        MPI_Request requests[commsize * 2]; 
        MPI_Status statuses[commsize * 2]; 

        if (rank == 0)
            start_time = MPI_Wtime();

        for (int i = 0; i < commsize; i++) {
            if (i != rank) {
                MPI_Isend(sbuf, n, MPI_CHAR, i, 0, MPI_COMM_WORLD, &requests[i]); 
                printf("Process %d sent message to process %d\n", rank, i);
            }
            MPI_Irecv(rbuf + i * n, n, MPI_CHAR, i, 0, MPI_COMM_WORLD, &requests[commsize + i]); 
        }

        MPI_Waitall(commsize * 2, requests, statuses);
        MPI_Barrier(MPI_COMM_WORLD);
        if (rank == 0)
            end_time = MPI_Wtime();

        for (int i = 0; i < commsize; i++) {
            if (i != rank) {
                printf("Process %d received message from process %d\n", rank, i); 
            }
        }

        if (rank == 0) {
            //fprintf(file, "%d %lf\n", 
                  //  n, end_time - start_time);
                printf("%d %lf\n", 
                       n, end_time - start_time);
        }

        free(rbuf);
        free(sbuf);
        n *= 1024; 
    }

    if (rank == 0) {
        fclose(file); 
    }

    MPI_Finalize();
    return 0;
}
