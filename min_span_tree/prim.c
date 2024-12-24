#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

void print_matrix(int *matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%6d ", matrix[i * n + j]);
        }
        printf("\n");
    }
}

void prim(int *graph, int n) {
    int *key = (int *)malloc(n * sizeof(int));      // Массив для минимальных ключей
    int *parent = (int *)malloc(n * sizeof(int));   // Массив для хранения родителей
    int *in_tree = (int *)calloc(n, sizeof(int));  // Массив для отслеживания вершин в дереве

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
        in_tree[i] = 0;
    }
    key[0] = 0; 

    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        int min_key = INT_MAX;
        for (int v = 0; v < n; v++) {
            if (!in_tree[v] && key[v] < min_key) {
                min_key = key[v];
                u = v;
            }
        }

        in_tree[u] = 1; 

        for (int v = 0; v < n; v++) {
            if (!in_tree[v] && graph[u * n + v] != 0 && graph[u * n + v] < key[v]) {
                key[v] = graph[u * n + v];
                parent[v] = u;
            }
        }
    }

    // printf("\nMST edges:\n");
    // for (int i = 1; i < n; i++) {
    //     printf("%d - %d: %d\n", parent[i], i, graph[parent[i] * n + i]);
    // }

    free(key);
    free(parent);
    free(in_tree);
}

int main() {
    int n = 10000;
    int *graph = (int *)malloc(n * n * sizeof(int));

    srand(42);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                graph[i * n + j] = 0; 
            } else {
                graph[i * n + j] = rand() % 10 + 1; 
                graph[j * n + i] = graph[i * n + j]; 
            }
        }
    }

    clock_t start_time = clock();  

    // print_matrix(graph, n); 
    prim(graph, n);

    clock_t end_time = clock();  

    
    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Count n: %d\n", n);
    printf("Elapsed time : %f\n", time_spent);
    printf("Count proc: 1");
    free(graph);
    return 0;
}
