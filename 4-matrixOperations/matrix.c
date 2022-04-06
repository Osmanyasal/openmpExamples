#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
static int isSizeEqual(Matrix *m, Matrix *n);

Matrix *Matrix_new(int i, int j)
{
    Matrix *m = (Matrix *)malloc(sizeof(Matrix));
    m->_i = i;
    m->_j = j;
    m->arr = (int **)malloc(i * sizeof(int *));
    for (int i = 0; i < j; i++)
        m->arr[i] = (int *)malloc(j * sizeof(int));

    return m;
}

PARALLEL_FUNC
Matrix *Matrix_add(Matrix *m, Matrix *n){
    if (!isSizeEqual(m, n))
        return NULL;

    Matrix *res = Matrix_new(m->_i, m->_j);
    
    #pragma omp parallel 
    {
        #pragma omp for
        for (int i = 0; i < m->_i; i++)
        {
            printf("TH %d\t",omp_get_thread_num());
            for (int j = 0; j < m->_j; j++){
                res->arr[i][j] = m->arr[i][j] + n->arr[i][j];
                printf("th %d\n",omp_get_thread_num());
            }
        }
    }
    return res;
}

PARALLEL_FUNC
Matrix *Matrix_sub(Matrix *m, Matrix *n)
{
    if (!isSizeEqual(m, n))
        return NULL;

    Matrix *res = Matrix_new(m->_i, m->_j);
    
    #pragma omp parallel 
    {
        #pragma omp for
        for (int i = 0; i < m->_i; i++)
        {
            printf("TH %d\t",omp_get_thread_num());
            for (int j = 0; j < m->_j; j++){
                res->arr[i][j] = m->arr[i][j] - n->arr[i][j];
                printf("th %d\n",omp_get_thread_num());
            }
        }
    }
    return res;
}

static int isSizeEqual(Matrix *m, Matrix *n)
{
    return m->_i == n->_i && m->_j == n->_j;
}

PARALLEL_FUNC
void Matrix_clear(Matrix *m)
{
#pragma omp parallel for
    for (int i = 0; i < m->_i; i++)
    {
        for (int j = 0; j < m->_j; j++)
            m->arr[i][j] = j + i;
    }
}

void Matrix_toString(Matrix *m)
{
    for (int i = 0; i < m->_i; i++)
    {
        for (int j = 0; j < m->_j; j++)
            printf("Matrix[%d][%d] = %d\t", i, j, m->arr[i][j]);
        printf("\n");
    }
}

void Matrix_destroy(Matrix *m)
{
    free(m);
}

