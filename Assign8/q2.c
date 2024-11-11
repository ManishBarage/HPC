#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int rank, size;
    int send_data, recv_data;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

 
    send_data = rank + 1;  
    printf("Process %d sending data: %d\n", rank, send_data);


    int right = (rank + 1) % size;
    int left = (rank - 1 + size) % size;

    MPI_Send(&send_data, 1, MPI_INT, right, 0, MPI_COMM_WORLD);


    MPI_Recv(&recv_data, 1, MPI_INT, left, 0, MPI_COMM_WORLD, &status);

    printf("Process %d received data: %d from process %d\n", rank, recv_data, left);

    MPI_Finalize();
    return 0;
}
