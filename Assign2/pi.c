#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include<time.h>

int main() {
    long long int num_points = 100000000;
    long long int points_in_circle = 0;
    double x, y;
    double pi;

    unsigned int seed = omp_get_thread_num();

    double start = omp_get_wtime();

    #pragma omp parallel for private(x, y, seed) reduction(+:points_in_circle)
    for (long long int i = 0; i < num_points; i++) {
        x = (double)rand_r(&seed) / RAND_MAX;
        y = (double)rand_r(&seed) / RAND_MAX;

        if (x * x + y * y <= 1.0) {
            points_in_circle++;
        }
    }

    double end = omp_get_wtime();

    pi = 4.0 * points_in_circle / num_points;

    printf("Calculated value of pi: %f\n", pi);
    printf("Time Taken for execution : %f\n", end-start);

    return 0;
}
