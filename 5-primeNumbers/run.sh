#!/bin/bash

#export OMP_NUM_THREADS=4
#echo "numThreads...: $OMP_NUM_THREADS"

export OMP_NUM_THREADS=8

gcc-11 -g -fopenmp *.c
[ "$#" -eq 1 ] && [ "$1" = "exec" ] && ./a.out



