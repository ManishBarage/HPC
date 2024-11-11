#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int rank, size;
    int n = 10; 
    int A[n];
    int local_sum = 0;
    int global_sum = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2)
    {
        if (rank == 0)
        {
            printf("This program requires exactly 2 processes.\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (rank == 0)
    {
        for (int i = 0; i < n; i++)
        {
            A[i] = i + 1; 
            printf("%d ",A[i]);
        }
        printf("\n");
    }

    MPI_Bcast(A, n, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (int i = 0; i < n / 2; i++)
        {
            local_sum += A[i];
        }
    }
    else
    {
        for (int i = n / 2; i < n; i++)
        {
            local_sum += A[i];
        }
    }

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("The sum of the array elements is: %d\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}