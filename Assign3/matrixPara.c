#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAX_SIZE 2000

void initialize_matrix(int *matrix, int size) {
    for (int i = 0; i < size * size; i++) {
        matrix[i] = rand() % 100;
    }
}

void print_matrix(int *matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i * size + j]);
        }
        printf("\n");
    }
}

void matrix_addition(int *A, int *B, int *C, int size, int num_threads) {
    #pragma omp parallel num_threads(num_threads)
    {
        #pragma omp for collapse(2)
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                C[i * size + j] = A[i * size + j] + B[i * size + j];
            }
        }
    }
}

double measure_time(int size, int num_threads) {
    int *A = (int *)malloc(size * size * sizeof(int));
    int *B = (int *)malloc(size * size * sizeof(int));
    int *C = (int *)malloc(size * size * sizeof(int));

    initialize_matrix(A, size);
    initialize_matrix(B, size);

    double start_time = omp_get_wtime();
    matrix_addition(A, B, C, size, num_threads);
    double end_time = omp_get_wtime();

    free(A);
    free(B);
    free(C);

    return end_time - start_time;
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int num_threads_list[] = {2, 4, 8};

    printf("Matrix Size,Threads,Time(s)\n");

    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        int size = sizes[i];
        for (int j = 0; j < sizeof(num_threads_list) / sizeof(num_threads_list[0]); j++) {
            int num_threads = num_threads_list[j];
            double time = measure_time(size, num_threads);
            printf("%d,%d,%f\n", size, num_threads, time);
        }

        printf("==========================================================\n");
    }

    return 0;
}
