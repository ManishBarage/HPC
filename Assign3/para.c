#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define VECTOR_SIZE 10

void bubble_sort_ascending(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_descending(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

double compute_dot_product(int *a, int *b, int size) {
    double dot_product = 0.0;

    #pragma omp parallel for reduction(+:dot_product)
    for (int i = 0; i < size; i++) {
        dot_product += a[i] * b[i];
    }

    return dot_product;
}

int main() {
    
    srand((unsigned int)time(NULL));

    int *vector1 = (int*)malloc(VECTOR_SIZE * sizeof(int));
    int *vector2 = (int*)malloc(VECTOR_SIZE * sizeof(int));

    
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector1[i] = rand() % 100;  
        vector2[i] = rand() % 100;  
    }

    printf("Vector 1:\n");
    for (int i = 0; i < VECTOR_SIZE; i++) {
        printf("%d ", vector1[i]);
    }
    printf("\n");

    printf("Vector 2:\n");
    for (int i = 0; i < VECTOR_SIZE; i++) {
        printf("%d ", vector2[i]);
    }
    printf("\n");

    
    bubble_sort_ascending(vector1, VECTOR_SIZE);

    
    bubble_sort_descending(vector2, VECTOR_SIZE);

    double start = omp_get_wtime();
    double ans = compute_dot_product(vector1, vector2, VECTOR_SIZE);
    double end = omp_get_wtime();

    printf("The minimum scalar product is: %.2f\n", ans);
    printf("The Execution Time : %f\n",end-start);

    free(vector1);
    free(vector2);

    return 0;
}
