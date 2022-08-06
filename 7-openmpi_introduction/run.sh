#!/bin/bash

#export OMP_NUM_THREADS=4
#echo "numThreads...: $OMP_NUM_THREADS"

#gcc-11 -g -fopenmp *.c && ./a.out
TMPDIR="/tmp"
mpicc -g -Wall -openmp -o mpi_hello *.c && mpiexec -np ${1-5} ./mpi_hello


