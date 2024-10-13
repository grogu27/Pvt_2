#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
    if (world_rank == 0) {
        // Процесс 0 отправляет сообщение процессу 1
        long int data = 1000;
        MPI_Send(&data, 1, MPI_LONG, 1, 0, MPI_COMM_WORLD);
        // Затем пытается получить сообщение от процесса 1
        MPI_Recv(&data, 1, MPI_LONG, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Процесс 0 получил данные %ld от процесса 1\n", data);
    }
    else if (world_rank == 1) {
        // Процесс 1 отправляет сообщение процессу 0
        long int data = 2000;
        MPI_Send(&data, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD);
        // Затем пытается получить сообщение от процесса 0
        MPI_Recv(&data, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Процесс 1 получил данные %ld от процесса 0\n", data);
    }
    
    MPI_Finalize();
    return 0;
}
