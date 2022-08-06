#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "macros/parallel.h"
#include "matrix.h"
#include "macros/ompwrapper.h"

int main(int argc, char *argv[])
{
    Matrix *m1 = Matrix_new(200,300);

    int m2[10][10];

    printf("%p\t%p\n",&m1->arr[0][0],&m1->arr[0][1]);
    printf("%p\t%p\n",&m1->arr[0][0],&m1->arr[1][0]);
    printf("----\n");
    printf("%p\t%p\n",&m2[0][0],&m2[0][1]);
    printf("%p\t%p\n",&m2[0][0],&m2[1][0]);

    free(m1);
}
