#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "macros/parallel.h"
#include "matrix.h"
#include "macros/ompwrapper.h"

int main(int argc, char *argv[])
{
    Matrix *m1 = Matrix_new(2,3);
    Matrix *m2 = Matrix_new(3,2);

    m1->arr[0][0] = 3;
    m1->arr[0][1] = -2;
    m1->arr[0][2] = 5;
 

    m1->arr[1][0] = 3;
    m1->arr[1][1] = 0;
    m1->arr[1][2] = 4;

    //000

    m2->arr[0][0] = 2;
    m2->arr[0][1] = 3;
 

    m2->arr[1][0] = -9;
    m2->arr[1][1] = 0;

    m2->arr[2][0] = 0;
    m2->arr[2][1] = 4;

    Matrix_toString(m1);

    printf("\n\n***\n\n");
    
    Matrix_toString(m2);

    Matrix *res = Matrix_mul(m1,m2);

    printf("\n\n***\n\n");
    Matrix_toString(res);
}
