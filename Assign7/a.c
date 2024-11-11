#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);  // Initialize the MPI environment

    printf("Hello World\n");

    MPI_Finalize();  // Finalize the MPI environment
    return 0;
}
