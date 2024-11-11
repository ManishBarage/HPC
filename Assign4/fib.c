#include <stdio.h>
#include <omp.h>

int fibonacci(int n) {
    if (n <= 1) return n;

    int x, y;

    #pragma omp task shared(x)
    x = fibonacci(n - 1);

    #pragma omp task shared(y) 
    y = fibonacci(n - 2);

    #pragma omp taskwait // Wait for both tasks to complete before proceeding
    return x + y;
}

int main() {
    int n = 30;
    int fib;

    double start_time = omp_get_wtime(); // Start timing

    #pragma omp parallel
    {
        #pragma omp single
        {
            fib = fibonacci(n);
        }
    }

    double end_time = omp_get_wtime(); // End timing

    printf("Fibonacci(%d) = %d\n", n, fib);
    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}
