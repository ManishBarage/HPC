#include <stdio.h>
#include <time.h>

#define SIZE 1000000

int main() {
    int array[SIZE];
    long long total_sum = 0;

    
    for (int i = 0; i < SIZE; i++) {
        array[i] = i+1; 
    }

    
    clock_t start = clock(); 

    for (int i = 0; i < SIZE; i++) {
        total_sum += array[i];
    }

    clock_t end = clock(); 

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Serial Total Sum: %lld\n", total_sum);
    printf("Execution Time: %f seconds\n", time_taken);

    return 0;
}
