#!/bin/bash

#export OMP_NUM_THREADS=4
#echo "numThreads...: $OMP_NUM_THREADS"

export OMP_SCHEDULE="static,1"
#gcc-11 -g -fopenmp *.c -L../libMath/ -lmath && ./a.out
gcc-11 -g -fopenmp *.c && ./a.out
#mpicc -openmp *.c && mpirun -np 2 ./a.out

