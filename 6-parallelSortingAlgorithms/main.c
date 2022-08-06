#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "macros/parallel.h"
#include "macros/ompwrapper.h"
#include "omp.h"

void oddEvenSort(int arr[], const int n, const int isParallel);
void oddEvenSortSingleParallel(int arr[], const int n, const int isParallel);

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int *createArray(int size)
{
    int *arr = (int *)malloc(sizeof(int) * size);
    for (int i = size; i > 0; i--)
    {
        arr[i] = i;
    }
    return arr;
}

int main(int argc, char *argv[])
{
    int n = 20000; // 500k
    int *arr = createArray(n);

    double start, end;
    double speedup = 0.0;
    start = omp_get_wtime();
    oddEvenSort(arr, n, 1);
    end = omp_get_wtime();
    speedup = (end - start);
    printf("parallel : %f\n", (end-start));

    int *arr2 = createArray(n);
    start = omp_get_wtime();
    oddEvenSort(arr2, n, 0);
    end = omp_get_wtime();
    printf("serial : %f\n", (end - start));

    speedup = (end-start) / speedup;

    printf("speedup %f\n",speedup);
    free(arr);
    free(arr2);

    printf("SİNGLE FOR \n");
    arr = createArray(n);
    start = omp_get_wtime();
    oddEvenSortSingleParallel(arr, n, 1);
    end = omp_get_wtime();
    speedup = (end - start);
    printf("parallel : %f\n", (end-start));

    arr2 = createArray(n);
    start = omp_get_wtime();
    oddEvenSortSingleParallel(arr2, n, 0);
    end = omp_get_wtime();
    printf("serial : %f\n", (end - start));

    speedup = (end-start) / speedup;

    printf("speedup %f\n",speedup);
    //printArray(arr, n);
    free(arr);
    free(arr2);
}
