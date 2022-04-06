#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "macros/parallel.h"
#include "prime.h"

int main(int argc, char *argv[])
{ 
     int verbose = 0;
     int printCount = 1;
     const int LIMIT = 500000;
     double start,end,serial,parallel;

     int iteration = 3;
     for(int i=0;i<iteration;i++){

          start = omp_get_wtime();
          printf("serial :\n");
          serialPrimeExec(LIMIT,printCount,verbose);
          end = omp_get_wtime();
          serial = (end-start);
          printf("****\ttime..%fms\n\n",serial);
     
          start = omp_get_wtime();
          printf("parallel :\n");
          parallelPrimeExec(LIMIT,printCount,verbose,1500);
          end = omp_get_wtime();
          parallel = (end-start);
          printf("****\ttime..%fms\n\n",parallel);

          printf("iteration %d\tspeedUp %f\n",iteration,(serial/parallel));

          printf("\n*******************************\n");
     }
}




