#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define ARR_SIZE 10000000

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int *arr = NULL;
    int *localArr = NULL;
    int localSum = 0;
    int totalSum = 0;
    int numElements = 0;
    int chunkSize = ARR_SIZE / (size - 1);
    int rem = ARR_SIZE % (size - 1);
    double startTime, endTime;

    if (rank == 0)
    {
        startTime = MPI_Wtime();
        arr = (int *)malloc(ARR_SIZE * sizeof(int));

        #pragma omp parallel for schedule(static)
        for (int i = 0; i < ARR_SIZE; i++)
        {
            arr[i] = 1; 
        }

        for (int i = 1; i < size; i++)
        {
            numElements = chunkSize + (i <= rem ? 1 : 0);
            int startIdx = (i - 1) * chunkSize + (i <= rem ? i - 1 : rem);

            MPI_Send(&numElements, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&arr[startIdx], numElements, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        free(arr);
    }
    else
    {
        numElements;
        MPI_Recv(&numElements, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        localArr = (int *)malloc(numElements * sizeof(int));
        MPI_Recv(localArr, numElements, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        #pragma omp parallel for reduction(+ : localSum) schedule(static)
        for (int i = 0; i < numElements; i++)
        {
            localSum += localArr[i];
        }

        free(localArr);
    }

    MPI_Reduce(&localSum, &totalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        endTime = MPI_Wtime();
        printf("Time taken: %f seconds\n", endTime - startTime);
        printf("Total sum: %d\n", totalSum);
    }
    MPI_Finalize();
    return 0;
}
