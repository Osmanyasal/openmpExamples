#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <omp.h>
 
#include "serialPi.h"
#include "parallelPi.h"

int main(int argc, char *argv[])
{
    printf("%f\n", serialPi());
    printf("%f\n", parallelPi());
    return EXIT_SUCCESS;
}