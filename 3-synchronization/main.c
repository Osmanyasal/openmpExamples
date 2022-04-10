#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int sh = 1;

    omp_set_num_threads(3);
    #pragma omp parallel shared(sh)
    {
        printf("TH %d\tsh %d\n",omp_get_thread_num(),sh);
        #pragma omp single
        {
            sh++; 
            printf("------\n");
        }
        printf("AFTER TH %d\tsh %d\n",omp_get_thread_num(),sh);        
    }
}
