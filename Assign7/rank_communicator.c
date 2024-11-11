#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);  // Initialize the MPI environment

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);  // Get the rank of the process

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);  // Get the number of processes

    if (world_rank < 5) {
        printf("Process %d is part of the communicator group with size %d\n", world_rank, world_size);
    }

    MPI_Finalize();  // Finalize the MPI environment
    return 0;
}
