#!/bin/bash

#export OMP_NUM_THREADS=4
#echo "numThreads...: $OMP_NUM_THREADS"

gcc-11 -fopenmp *.c && ./a.out



