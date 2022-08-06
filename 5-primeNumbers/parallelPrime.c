#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include "prime.h"

// 2 3 5 7 13
// 17 19 23 etc.
typedef struct ParallelPrimeNode
{
    int *localPrimeList;
    int localIndex;
    int localLimit;
    struct ParallelPrimeNode *next;
} ParallelPrimeNode;

static bool isLocalPrime(ParallelPrimeNode *node, int num);
static void evaluate(ParallelPrimeNode *node, int num);
static ParallelPrimeNode *ParallelPrime_new(int localLimit)
{
    ParallelPrimeNode *node = (ParallelPrimeNode *)malloc(sizeof(ParallelPrimeNode));
    node->localLimit = localLimit;
    node->localIndex = 0;
    node->localPrimeList = (int *)malloc(sizeof(int) * node->localLimit);
    node->next = NULL;
    return node;
}

static void evaluate(ParallelPrimeNode *node, int num)
{
    bool isPrime = isLocalPrime(node, num);
    if (isPrime && (node->localLimit > node->localIndex))
    {
#pragma omp critical
        node->localPrimeList[(node->localIndex)++] = num;
    }
    else if (isPrime)
    {
        if (node->next == NULL)
        {
#pragma omp critical
            {
                if (node->next == NULL)
                    node->next = (ParallelPrimeNode *)ParallelPrime_new(node->localLimit);
            }
        }
        evaluate(node->next, num);
    }
}

static bool isLocalPrime(ParallelPrimeNode *node, int num)
{
    bool isPrime = true;
    if (num == 2 || num == 3 || num == 5 || num == 7 || num == 11 || num == 13)
        return isPrime;

    int tmp = node->localIndex;
    for (int i = 0; i < tmp; i++)
    {
        int arrNum = node->localPrimeList[i];
        if (arrNum == 0)
            continue;
        else if (num % arrNum == 0)
        {
            isPrime = false;
            break;
        }
    }
    return isPrime;
}

void parallelPrimeExec(const int limit, int printCount, int verbose, int localSize)
{
    ParallelPrimeNode *head = ParallelPrime_new(localSize);

#pragma omp parallel
    {
#pragma omp for schedule(dynamic) nowait // 2 100 -> 2 40, 41 60,
        for (int i = 2; i < limit; i++)
        {
            evaluate(head, i);
        }
    } // implied barrier here

    ParallelPrimeNode *tmp = head;
    int len = 0;
    while (tmp != NULL)
    {
        if (verbose)
            printArray(tmp->localPrimeList, tmp->localIndex);
        len += tmp->localIndex;
        tmp = tmp->next;
    }
    printf("size..:%d\n", len);
    free(head);
}