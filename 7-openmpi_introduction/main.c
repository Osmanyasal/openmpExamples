#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/local/Cellar/gcc/11.3.0/lib/gcc/11/gcc/x86_64-apple-darwin21/11/include/omp.h"
#include <mpi.h>
#include <time.h>

const int MAX_STRING = 100;

void treeReduction();
void autoReduction();
void autoAllReduction();
void simpleBroadCast();
void singleSending();
void groupSending();

int main(int argc, char *argv[])
{
    simpleBroadCast();
    return 0;
}
void groupSending()
{
    double start, end, execTime = 0;
    start = MPI_Wtime();

    int commSize;
    int commId;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &commId);

    const short ARR_SIZE = 100;
    int arr[ARR_SIZE];
    if (commId == 0)
        MPI_Ssend(arr, ARR_SIZE, MPI_INTEGER, 1, 0, MPI_COMM_WORLD);
    else if (commId == 1)
        MPI_Recv(arr, ARR_SIZE, MPI_INTEGER, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // printf("\n[");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        // printf("%d,", arr[i]);
    }
    // printf("\b]\n");
    end = MPI_Wtime();
    double localExecTime = end - start;
    MPI_Reduce(&localExecTime, &execTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    if (commId == 0)
        printf("time elapse : %f\n", execTime);
    MPI_Finalize();
}

void singleSending()
{
    int commSize;
    int commId;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &commId);

    if (commId == 0)
        printf("commSize %d\n", commSize);

    const short ARR_SIZE = 100;
    int arr[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; i++)
        arr[i] = i;
    if (commId == 0)
        for (int i = 0; i < ARR_SIZE; i++)
            MPI_Ssend(&arr[i], 1, MPI_INTEGER, 1, 0, MPI_COMM_WORLD);
    else if (commId == 1)
    {
        int number = 0;
        // printf("\n[");
        for (int i = 0; i < ARR_SIZE; i++)
        {
            MPI_Recv(&number, 1, MPI_INTEGER, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // printf("%d,", number);
        }
        // printf("\b]\n");
    }
    MPI_Finalize();
}

void simpleBroadCast()
{
    int commSize;
    int commId;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &commId);

    int number = -1;
    int number2 = -2;
    if (commId == 0)
    {
        number = 10;
        number2 = 20;
    }

    MPI_Bcast(&number, 1, MPI_INTEGER, 0, MPI_COMM_WORLD);
    MPI_Bcast(&number2, 1, MPI_INTEGER, 0, MPI_COMM_WORLD);

    printf("id[%d]  number : %d\n", commId, number);
    printf("id[%d]  number2 : %d\n", commId, number2);

    MPI_Finalize();
}

void autoAllReduction()
{
    int commSize;
    int commId;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &commId);

    int result = 0;
    int i = 5;
    /* ALL the processes have the final sum */
    MPI_Allreduce(&i, &result, 1, MPI_INTEGER, MPI_SUM, MPI_COMM_WORLD);
    printf("This is result of %d : %d\n", commId, result);

    MPI_Finalize();
}

void autoReduction()
{
    int commSize;
    int commId;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &commId);

    int result = 0;
    int i = 5;
    /* Only target processes have the final sum */
    MPI_Reduce(&i, &result, 1, MPI_INTEGER, MPI_SUM, 0, MPI_COMM_WORLD);

    printf("This is result of %d : %d\n", commId, result);

    MPI_Finalize();
}

void treeReduction()
{
    char greeting[MAX_STRING];
    int commSize;
    int commId;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &commId);

    int upperLimit = commSize;
    int commTempSize = upperLimit / 2;
    while (commTempSize > 0 && commId <= upperLimit)
    {
        if (commId >= commTempSize)
        {
            sprintf(greeting, "Greetings from process %d of %d!", commId, commSize);
            MPI_Ssend(greeting, strlen(greeting) + 1, MPI_CHAR, (commId - commTempSize), 0,
                      MPI_COMM_WORLD);
        }
        else if (commId < commTempSize)
        {
            printf("\nTHIS IS CORE: %d of %d!\n\n", commId,
                   commSize);
            MPI_Recv(greeting, MAX_STRING, MPI_CHAR, (commId + commTempSize), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // printf("%s\n", greeting);
        }
        commTempSize = commTempSize / 2;
        upperLimit = upperLimit / 2;
    }
    MPI_Finalize();
}
