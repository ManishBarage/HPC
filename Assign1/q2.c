#include<stdio.h>
#include<omp.h>

int main()
{
    int n;
    printf("Enter the number of threads : ");
    scanf("%d", &n);

    printf("Sequential : \n");

    for(int i=0;i<n;i++)
    {
        printf("Hello WOrld !\n");
    }

    omp_set_num_threads(n);
    printf("Parallel : \n");
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        printf("Hello World : Thread Id : %d \n",id);
    }
}