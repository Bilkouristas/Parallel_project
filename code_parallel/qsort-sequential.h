  /**********************************************************************
 *
 * qsort-sequential.h -- Sequential implementation of QuickSort
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Time-stamp: <2018-10-10>
 *
 **********************************************************************/


#ifndef _QSORT_SEQUENTIAL_H_
#define _QSORT_SEQUENTIAL_H_

/* qsortseq -- Sort vector v (of length n) using QuickSort */
void qsort_seq(int *v, int n);

struct thread_data {
int *array;
int len;
};

void cilksort(int *a,int n, int worker_num);

void parqsort(int *a, int n,int thread_num);

void omp_qsort(int *a, int n,int thread_num);

int partition(int *v, int n);

void setWorkerz(char *n);


extern const int minSize;
void print(int *a, int n);

#endif /* _QSORT-SEQUENTIAL_H_ */
