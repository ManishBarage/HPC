#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int rank, size;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("This program requires at least 2 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }


    if (rank == 0) {
        int message = 1;
        MPI_Recv(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); 

        printf("Process 0 received message: %d\n", message);
    } else if (rank == 1) {
        int message = 2;
        MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Send(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
        printf("Process 1 sent message: %d\n", message);
    }

    MPI_Finalize();
    return 0;
}
