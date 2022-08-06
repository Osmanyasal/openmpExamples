#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matrix.h"
#include "macros/ompwrapper.h"

static bool isSizeEqual(Matrix *m, Matrix *n);
static bool isMulSizeEqual(Matrix *m, Matrix *n);

Matrix *Matrix_new(int i, int j)
{
    Matrix *m = (Matrix *)malloc(sizeof(Matrix));
    m->_i = i;
    m->_j = j;
    m->arr = (int **)malloc(i * sizeof(int*));
    for (int i = 0; i < m->_i; i++)
        m->arr[i] = (int *)malloc(j * sizeof(int));
    return m;
}

PARALLEL_FUNC
Matrix *Matrix_mul(Matrix *m, Matrix *n)
{
    Matrix *res = NULL;
    if (isMulSizeEqual(m, n))
        res = (Matrix *)Matrix_new(m->_i, n->_j);
    else{
        perror("Sizes are not appropriate to eachother!!");
        return res;
    }
    #pragma omp parallel for
    for (int i = 0; i < m->_i; i++) // res->_i
        for (int j = 0; j < n->_j; j++) // res->_j
            for (int k = 0; k < m->_j; k++)
                res->arr[i][j] += m->arr[i][k] * n->arr[k][j];
    return res;
}

static bool isMulSizeEqual(Matrix *m, Matrix *n)
{
    return m->_j == n->_i;
}

PARALLEL_FUNC
Matrix *Matrix_add(Matrix *m, Matrix *n)
{
    if (!isSizeEqual(m, n))
        return NULL;

    Matrix *res = Matrix_new(m->_i, m->_j); 
#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < m->_i; i++)
        {
            printf("TH %d\t", omp_get_thread_num());
            for (int j = 0; j < m->_j; j++)
            {
                res->arr[i][j] = m->arr[i][j] + n->arr[i][j];
                printf("th %d\n", omp_get_thread_num());
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
            printf("TH %d\t", omp_get_thread_num());
            for (int j = 0; j < m->_j; j++)
            {
                res->arr[i][j] = m->arr[i][j] - n->arr[i][j];
                printf("th %d\n", omp_get_thread_num());
            }
        }
    }
    return res;
}

static bool isSizeEqual(Matrix *m, Matrix *n)
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
    if (m == NULL)
    {
        perror("Matrix is NULL");
        return;
    }
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
