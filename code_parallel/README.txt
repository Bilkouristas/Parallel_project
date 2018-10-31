Cilk implementation: cilksort.c
Pthreads implementation: parqsort.c
OpenMP implementation: omp_qsort.c
Sequential implementation (given): qsort-sequential.c

qsort-main calls all of the above, plus the standard library qsort and records
the time they take.

The header file qsort-sequential.h is common among all of the above and they all
use the same partition + swap functions.
