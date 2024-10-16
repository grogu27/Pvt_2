#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int rank, commsize;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int n = 1024; // Размер сообщения
    FILE *file = NULL;

    if (rank == 0) {
        file = fopen("result.txt", "w");
        if (file == NULL) {
            printf("Ошибка открытия файла!\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }
    for (int i = 0; i <= 1; i++) {
        // Выделяем память для буфера
        char *sbuf = (char*)malloc(n * sizeof(char));
        char *rbuf = (char*)malloc(n * commsize * sizeof(char)); // Буфер для получения всех сообщений

        if (sbuf == NULL || rbuf == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        // Заполнение сообщения случайными данными
        for (int b = 0; b < n; b++) {
            sbuf[b] = rand() % 128; // Заполнение sbuf случайными значениями
        }

        MPI_Request requests[commsize * 2]; // Массив для хранения запросов
        MPI_Status statuses[commsize * 2]; // Массив для статусов

        double start_time = MPI_Wtime();

        // Неблокирующая отправка сообщений всем процессам
        for (int i = 0; i < commsize; i++) {
            if (i != rank) {
                MPI_Isend(sbuf, n, MPI_CHAR, i, 0, MPI_COMM_WORLD, &requests[i]); // Отправка сообщения
                printf("Process %d sent message to process %d\n", rank, i);
            }
            MPI_Irecv(rbuf + i * n, n, MPI_CHAR, i, 0, MPI_COMM_WORLD, &requests[commsize + i]); // Приём сообщения
        }

        MPI_Waitall(commsize * 2, requests, statuses); // Ожидание завершения всех операций

        double end_time = MPI_Wtime();

        for (int i = 0; i < commsize; i++) {
            if (i != rank) {
                printf("Process %d received message from process %d\n", rank, i); // Вывод информации о получении
            }
        }

        // Запись результатов в файл
        if (rank == 0) {
            fprintf(file, "Message size: %d, Time = %lf\n", 
                    n, end_time - start_time);
                // printf("Message size: %d, Time = %lf\n", 
                //        n, end_time - start_time);
        }

        // Освобождение памяти
        free(rbuf);
        free(sbuf);
        n *= 1024; 
    }

    if (rank == 0) {
        fclose(file); // Закрытие файла
    }

    MPI_Finalize();
    return 0;
}
