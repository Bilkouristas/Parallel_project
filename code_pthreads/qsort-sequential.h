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
int right;
int current_depth;
int depth;
};

void parqsort(int *a, int n,int thread_num);

int partition(int *v, int n);

void print(int *a, int n);

#endif /* _QSORT-SEQUENTIAL_H_ */
