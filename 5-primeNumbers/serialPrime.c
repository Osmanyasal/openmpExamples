#include <stdio.h>
#include <stdlib.h>
#include "prime.h"

int *findPrimeNumbersUpto(int num, int *len)
{
    int *arr = malloc(sizeof(int) * num);
    int arrIndex = 0;
    int flag = 1;
    for (int i = 2; i < num; i++)
    {
        if (i == 2 || i == 3 || i == 5 || i == 7 || i == 11 || i == 13)
            arr[arrIndex++] = i;
        else
        {
            for (int m = 0; m < arrIndex; m++)
            {
                if (i % arr[m] == 0)
                {
                    flag = 0;
                    break;
                }
            }
            if (!flag)
            {
                flag = 1;
            }
            else
            {
                arr[arrIndex++] = i;
            }
        }
    }
    *len = arrIndex;
    return arr;
}

void serialPrimeExec(const int limit, int printCount, int verbose)
{
    int len = 0;
    int *res = findPrimeNumbersUpto(limit, &len);
    if (verbose)
        printArray(res, len);
    if (printCount)
        printf("size..:%d\n", len);
    free(res);
}