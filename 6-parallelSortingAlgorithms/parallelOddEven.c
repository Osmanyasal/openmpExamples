#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "macros/parallel.h"
#include "macros/ompwrapper.h"
#include "omp.h"

/**
 * @brief Parallel odd even sort algorithm based on bubble sorting
 * O(n**2)
 *
 * @param arr array itself
 * @param n size
 * @param isParallel if 1 sort parallel if 0 sort serial
 */
void oddEvenSort(int arr[], const int n, const int isParallel)
{
    bool isSorted = false; // Initially array is unsorted
    while (!isSorted)
    {
        isSorted = true;

#pragma omp parallel for if (isParallel)
        for (int i = 1; i <= n - 2; i = i + 2)
        {
            if (arr[i] > arr[i + 1])
            {
                int temp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = temp;
                isSorted = false;
            }
        }

#pragma omp parallel for if (isParallel)
        for (int i = 0; i <= n - 2; i = i + 2)
        {
            if (arr[i] > arr[i + 1])
            {
                int temp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = temp;
                isSorted = false;
            }
        }
    }
    return;
}

/**
 * @brief Parallel odd even sort algorithm based on bubble sorting
 * O(n**2)
 *
 * @param arr array itself
 * @param n size
 * @param isParallel if 1 sort parallel if 0 sort serial
 */
void oddEvenSortSingleParallel(int arr[], const int n, const int isParallel)
{
    bool isSorted = false;
    while(!isSorted)
    {
        isSorted = true;
        #pragma omp parallel if(isParallel)
            {
                #pragma omp for
                for (int i = 1; i <= n - 2; i = i + 2)
                {
                    if (arr[i] > arr[i + 1])
                    {
                        int temp = arr[i + 1];
                        arr[i + 1] = arr[i];
                        arr[i] = temp;
                        isSorted = false;
                    }
                } // implied barrier here!

                #pragma omp for
                for (int i = 0; i <= n - 2; i = i + 2)
                {
                    if (arr[i] > arr[i + 1])
                    {
                        int temp = arr[i + 1];
                        arr[i + 1] = arr[i];
                        arr[i] = temp;
                        isSorted = false;
                    }
                } // implied barrier here!
            }
    }
}