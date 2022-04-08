#ifdef _OPENMP
    #include <omp.h>
    #define omp_version() _OPENMP
#else
    #define omp_get_thread_num() 0
    #define omp_get_num_threads() 1
#endif