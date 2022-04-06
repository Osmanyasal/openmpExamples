#include <omp.h>
#include <stdio.h>

static long numSteps = 1000000;
double serialPi(void)
{

    double start = omp_get_wtime();
    int i;
    double x;
    double pi;
    double sum = 0;
    double step;

    step = 1.0 / (numSteps);
    for (i = 0; i < numSteps; i++)
    {
        x = (i + .5) * step;
        sum += 4.0 / (1 + x * x);
    }
    pi = step * sum;

    double end = omp_get_wtime();
    printf("serial time..:%f\n",(end-start));
    return pi;
}
