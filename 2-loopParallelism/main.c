#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

extern void sumBenchmark();
int main(int argc,char *argv[]){

    //sumBenchmark();
    #pragma omp parallel num_threads(10)
    {
        printf("hello world %d\n",omp_get_thread_num());

        #pragma omp single
        {   
            printf("inner world %d\n",omp_get_thread_num());
        }
    }   
    printf("\n~~~goodbye world\n");

    return EXIT_SUCCESS;
}

void sumBenchmark(){

    const long int LIMIT = 500000000l;    // 500_000_000
    long int result = 0l;
    double start = omp_get_wtime();
    
    omp_set_num_threads(omp_get_max_threads());
    #pragma omp parallel for reduction(+:result)
    for(long int i=1; i < LIMIT; i++){
        result = result + i;
    }
    
    double end = omp_get_wtime();
    printf("parallel result ..: %lu\t%f ms\n",result,(end-start));


    start = omp_get_wtime();
    result = 0;
    for(long int i=1; i < LIMIT; i++){
        result = result + i;
    }
    end = omp_get_wtime();
    printf("serial result ..: %lu\t%f ms\n",result,(end-start));
}