#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc,char *argv[]){
    
    omp_set_num_threads(8);
    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            printf("this is thread [%d] and we created %d threads\n",omp_get_thread_num(),omp_get_num_threads());
        }
        printf("is %d okay?\n",omp_get_thread_num());
    }
}
