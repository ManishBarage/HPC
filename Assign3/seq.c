#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VECTOR_SIZE 1000000


int compare_asc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

double compute_scalar_product_sequential(const int *vector1, const int *vector2, int size) {
    double product_sum = 0;
    for (int i = 0; i < size; i++) {
        product_sum += (double)(vector1[i] * vector2[i]);
    }
    return product_sum;
}

int main() {
    int *vector1 = (int *)malloc(VECTOR_SIZE * sizeof(int));
    int *vector2 = (int *)malloc(VECTOR_SIZE * sizeof(int));

    if (vector1 == NULL || vector2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Seed random number generator
    srand((unsigned int)time(NULL));

    // Populate vectors with random values
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector1[i] = rand() % 100;
        vector2[i] = rand() % 100;
    }

    // Sort vectors
    qsort(vector1, VECTOR_SIZE, sizeof(int), compare_asc);
    qsort(vector2, VECTOR_SIZE, sizeof(int), compare_asc);

    // Sequential computation
    clock_t start_time, end_time;
    double duration;

    start_time = clock();
    double scalar_product = compute_scalar_product_sequential(vector1, vector2, VECTOR_SIZE);
    end_time = clock();

    duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Sequential scalar product result: %.2f\n", scalar_product);
    printf("Time taken for sequential computation: %.6f seconds\n", duration);

    // Free allocated memory
    free(vector1);
    free(vector2);

    return 0;
}
