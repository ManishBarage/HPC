#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void solve(double *vector, double scalar, int size, int n_threads)
{

    #pragma omp parallel for num_threads(n_threads)
    for(int i=0;i<size;i++)
    {
        vector[i] += scalar;
    }
}

int main()
{
    int size = 1000000;
    double scalar = 5.0;

    int tot_thread[] = {1,2,4,8};

    double *arr = (double *) malloc(size * sizeof(double));

    for(int i=0;i<size;i++)
    {
        arr[i] = (double)i;
    }

    for(int i=0;i<sizeof(tot_thread)/sizeof(tot_thread[0]);i++)
    {
        double start = omp_get_wtime();
        solve(arr,scalar,size,tot_thread[i]);
        double end = omp_get_wtime();

        printf("Total Threads : %d, Time Taken : %f Seconds \n", tot_thread[i], end-start);
    }
    free(arr);
    return 0;
}