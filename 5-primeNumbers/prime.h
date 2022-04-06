#ifndef _PRIME_H
#define _PRIME_H

extern void serialPrimeExec(const int limit, int printCount, int verbose);
extern void parallelPrimeExec(const int limit, int printCount, int verbose, int localSize);

static int *findPrimeNumbersUpto(int num, int *len);
static void printArray(int *arr, int size)
{
    printf("[");
    for (int i = 0; i < size; i++)
        printf("%d,", arr[i]);
    printf("\b]\n");
}

#endif