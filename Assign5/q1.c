#include <stdio.h>
#include <omp.h>


double sequential() {
    const char *family_members[] = {
        "Manish",
        "Bob",
        "Charlie",
        "Diana",
        "Eve"
    };
    int num_family_members = sizeof(family_members) / sizeof(family_members[0]);


    double start_time = omp_get_wtime();

    for (int i = 0; i < num_family_members; i++) {
        printf("Member %d: %s\n", i, family_members[i]);
    }

    double end_time = omp_get_wtime(); 

    return end_time - start_time;
}

double parallel() {
    const char *family_members[] = {
        "Manish",
        "Bob",
        "Charlie",
        "Diana",
        "Eve"
    };
    int num_family_members = sizeof(family_members) / sizeof(family_members[0]);


    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        
        if (thread_id < num_family_members) {
            printf("Thread %d: %s\n", thread_id, family_members[thread_id]);
        }
    }

    double end_time = omp_get_wtime();
    
    return end_time - start_time;
}

int main() {
    double seq =  seqsequential();
    double para = parallel();

    double speed_up = seq/para;

    printf("Speed Up is : %f", speed_up);

}
