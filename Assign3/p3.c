#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define VECTOR_SIZE 200 


void init_vec(int *vec, int size) {
    for (int i = 0; i < size; i++) {
        vec[i] = rand() % 100;
    }
}

void add_static(int *vec, int scalar, int size, int chunk) {
    #pragma omp parallel for schedule(static, chunk)
    for (int i = 0; i < size; i++) {
        vec[i] += scalar;
    }
}


void add_dynamic(int *vec, int scalar, int size, int chunk) {
    #pragma omp parallel for schedule(dynamic, chunk)
    for (int i = 0; i < size; i++) {
        vec[i] += scalar;
    }
}

void add_nowait(int *vec, int scalar, int size) {
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < size; i++) {
            vec[i] += scalar;
        }
    }
}

int main() {
    int vec[VECTOR_SIZE];
    int scalar = 10; 
    int chunks[] = {1, 10, 50, 100};

   
    init_vec(vec, VECTOR_SIZE);

    printf("STATIC Schedule:\n");
    for (int i = 0; i < 4; i++) {
        double start_time = omp_get_wtime();
        add_static(vec, scalar, VECTOR_SIZE, chunks[i]);
        double end_time = omp_get_wtime();
        printf("Chunk size: %d, Time: %.6f seconds\n", chunks[i], end_time - start_time);
    }

    printf("\nDYNAMIC Schedule:\n");
    for (int i = 0; i < 4; i++) {
        double start_time = omp_get_wtime();
        add_dynamic(vec, scalar, VECTOR_SIZE, chunks[i]);
        double end_time = omp_get_wtime();
        printf("Chunk size: %d, Time: %.6f seconds\n", chunks[i], end_time - start_time);
    }
    printf("\nUsing nowait clause:\n");
    double start_time = omp_get_wtime();
    add_nowait(vec, scalar, VECTOR_SIZE);
    double end_time = omp_get_wtime();
    printf("Nowait clause, Time: %.6f seconds\n", end_time - start_time);

    return 0;
}
