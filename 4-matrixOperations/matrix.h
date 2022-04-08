#include <stdio.h>
#include <stdlib.h>
#include "macros/parallel.h"
#include "macros/ompwrapper.h"

typedef struct Matrix
{
    int **arr;  // 2D array
    int _i;     // lines
    int _j;     // columns
} Matrix;

extern Matrix *Matrix_new(int i, int j);
extern void Matrix_toString(Matrix *m);
extern void Matrix_destroy(Matrix *m);

PARALLEL_FUNC
extern void Matrix_clear(Matrix *m);

PARALLEL_FUNC
extern Matrix *Matrix_add(Matrix *m, Matrix *n);

PARALLEL_FUNC
extern Matrix *Matrix_sub(Matrix *m, Matrix *n);
 
PARALLEL_FUNC
extern Matrix *Matrix_mul(Matrix *m, Matrix *n);
