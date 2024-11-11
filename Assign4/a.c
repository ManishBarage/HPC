#include<stdio.h>
#include<omp.h>

int main(){
    int total= 0;

    omp_set_num_threads(10);
    #pragma omp parallel for lastprivate(total)
    for(int i = 0; i < 10; i++){
        total += i;
        printf("Thread %d: partial sum = %d\n", omp_get_thread_num(), total);
    }

    printf("Final total: %d\n", total);

    return 0;
}