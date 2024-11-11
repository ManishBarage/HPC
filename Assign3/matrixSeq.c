#include <stdio.h>
#include <stdlib.h>
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

void matrix_addition_sequential(int *A, int *B, int *C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i * size + j] = A[i * size + j] + B[i * size + j];
        }
    }
}

double measure_time(int size) {
    int *A = (int *)malloc(size * size * sizeof(int));
    int *B = (int *)malloc(size * size * sizeof(int));
    int *C = (int *)malloc(size * size * sizeof(int));

    initialize_matrix(A, size);
    initialize_matrix(B, size);

    double start_time = (double)clock() / CLOCKS_PER_SEC;
    matrix_addition_sequential(A, B, C, size);
    double end_time = (double)clock() / CLOCKS_PER_SEC;

    free(A);
    free(B);
    free(C);

    return end_time - start_time;
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};

    printf("Matrix Size,Time(s)\n");

    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        int size = sizes[i];
        double time = measure_time(size);
        printf("%d,%f\n", size, time);
    }

    return 0;
}
