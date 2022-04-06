#include <omp.h>
#include <stdio.h>

static long numSteps = 100000;
static double serialPi(int start, int end);
double parallelPi(void)
{
    double start = omp_get_wtime();

    const int THREAD_COUNT = 8;
    int actualThreadNums = 0;
    double arr[THREAD_COUNT];

    omp_set_num_threads(THREAD_COUNT);
    #pragma omp parallel
    {
        if (omp_get_thread_num() == 0)
        {
            actualThreadNums = omp_get_num_threads();
            printf("ACTUAL THREAD COUNT : %d\n", actualThreadNums);
        }
        while(actualThreadNums == 0);
        int startt = numSteps / actualThreadNums;
        int id = omp_get_thread_num();
        // printf("%d\t from:%d\tto:%d\n",id,12500*id,12500*id + 12500);
        arr[id] = serialPi(startt * id, startt * id + startt);
    }
    double total = 0;
    for (short i = 0; i < actualThreadNums; i++)
    {
        total += arr[i];
    }
    double end = omp_get_wtime();
    printf("parallel time..:%f\n", (end - start));
    return total;
}

static double serialPi(int start, int end)
{
    int i;
    double x;
    double pi;
    double sum = 0;
    double step;

    step = 1.0 / (end - start);
    for (i = start; i < end - start; i++)
    {
        x = (i + .5) * step;
        sum += 4.0 / (1 + x * x);
    }
    pi = step * sum;
    return pi;
}
