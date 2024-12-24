#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <mpi.h>

#define INF INT_MAX

void print_matrix(int *matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%6d ", matrix[i * n + j]);
        }
        printf("\n");
    }
}

void get_chunk(int rank, int size, int n, int *lb, int *ub) {
    *lb = rank * (n / size); 
    *ub = (rank + 1) * (n / size) - 1; 
    if (rank == size - 1) {
        *ub = n - 1; 
    }
}

void find_local_min(int rank, int size, int n, int *d, int *in_tree, int *local_min_value, int *local_min_index) {
    int lb, ub;

    get_chunk(rank, size, n, &lb, &ub);

    *local_min_value = INF;
    *local_min_index = -1;

    for (int i = lb; i <= ub; i++) {
        if (!in_tree[i] && d[i] < *local_min_value) {
            *local_min_value = d[i];
            *local_min_index = i;
        }
    }
}

void update_distances(int n, int *d, int *in_tree, int global_min_index, int *graph, int *parent) {
    for (int i = 0; i < n; i++) {
        if (!in_tree[i] && graph[global_min_index * n + i] < d[i]) {
            d[i] = graph[global_min_index * n + i];
            parent[i] = global_min_index;
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size, n;
    int *d, *in_tree, *parent, *graph;
    int local_min_value, local_min_index, global_min_value, global_min_index;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    n = 10000; 
    graph = (int *)malloc(n * n * sizeof(int));
    d = (int *)malloc(n * sizeof(int));
    in_tree = (int *)malloc(n * sizeof(int));
    parent = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        d[i] = INF; // Изначально все расстояния равны INF
        in_tree[i] = 0; // Все вершины вне дерева
        parent[i] = -1; // Нет родителей
    }
    d[0] = 0; 

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                graph[i * n + j] = 0; 
            } else {
                graph[i * n + j] = rand() % 30 + 3; 
                graph[j * n + i] = graph[i * n + j]; 
            }
        }
    }
    // if (rank == 0)
    //     print_matrix(graph, n);
    if (rank == 0)
        start_time = MPI_Wtime();

    for (int i = 0; i < n - 1; i++) {
        find_local_min(rank, size, n, d, in_tree, &local_min_value, &local_min_index);

        // Синхронизация локальных минимумов между процессами
        MPI_Allreduce(&local_min_value, &global_min_value, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
        MPI_Allreduce(&local_min_index, &global_min_index, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);

        // Если найден новый минимальный элемент
        if (global_min_value != INF) {
            in_tree[global_min_index] = 1; 
            update_distances(n, d, in_tree, global_min_index, graph, parent);
        }
    }
    if (rank == 0)
        end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Count n: %d\n", n);
        printf("Count proc: %d\n", size);
        printf("MST edges:\n");
        // for (int i = 1; i < n; i++) {
        //     printf("Edge: %d - %d, Weight: %d\n", parent[i], i, graph[parent[i] * n + i]);
        // }
        printf("Elapsed time : %f sec.\n", end_time - start_time);
    }

    free(graph);
    free(d);
    free(in_tree);
    free(parent);
    MPI_Finalize();
    return 0;
}
