/**********************************************************************
 *
 * qsort.c -- Sequential implementation of QuickSort
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Time-stamp: <2018-10-10>
 *
 **********************************************************************/
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "qsort-sequential.h"
#include <assert.h>
#include <string.h>

/* local function declarations */
int  test( int *a, int n);
void init( int *a, int n);
void print(int *a, int n);
int comparetor (const void * a, const void * b);


/* --- Entry POINT --- */
int main(int argc, char **argv) {

  /* parse input */
  if (argc != 3) {
    printf("Usage: %s q\n  where n1=2^q is problem size (power of two) and n2=2^p is thread limit (power of two) \n",
	   argv[0]);
    exit(1);
  }
  printf("Q=%d , P=%d \n",atoi(argv[1]),atoi(argv[2]));

  /* variables to hold execution time */
  struct timeval startwtime, endwtime;
  double seq_time;
  double par_thr_time;
  double cilk_time;
  double omp_time;
  double std_time;
  int pass;

  /* initiate vector of random integers */
  int n  = 1<<atoi(argv[1]);
  int thread_num = 1<<atoi(argv[2]);
  int *a = (int *) malloc(n * sizeof(int));
  int *p_a= (int *) malloc(n* sizeof(int));
  int *cilk_a=(int *) malloc(n* sizeof(int));
  int *omp_a=(int *) malloc(n* sizeof(int));
  int *std_a=(int *) malloc(n* sizeof(int));

  /* initialize vector */
  init(a, n);
  memcpy(p_a,a,sizeof(int)*n);
  memcpy(cilk_a,a,sizeof(int)*n);
  memcpy(omp_a,a,sizeof(int)*n);
  memcpy(std_a,a,sizeof(int)*n);


  /* print vector */
  /* print(a, n); */

  // >>>      CILK      <<<
 //  >>> IMPLEMENTATION <<<
//   >>>      HERE      <<<


  gettimeofday (&startwtime, NULL);
  cilksort(cilk_a, n,thread_num);
  gettimeofday (&endwtime, NULL);

  /* get time in seconds */
  cilk_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
  + endwtime.tv_sec - startwtime.tv_sec);

  pass = test(cilk_a, n);
  printf("CILK TEST %s\n",(pass) ? "PASSED" : "FAILED");
  // assert( pass != 0 );
  printf("  ->Cilk wall clock time: %f sec\n", cilk_time);


  // >>>     OPENMP     <<<
 //  >>> IMPLEMENTATION <<<
//   >>>      HERE      <<<


  gettimeofday (&startwtime, NULL);
  omp_qsort(omp_a, n,thread_num);
  gettimeofday (&endwtime, NULL);

  /* get time in seconds */
  omp_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
  + endwtime.tv_sec - startwtime.tv_sec);

  pass = test(omp_a, n);
  printf("OPENMP TEST %s\n",(pass) ? "PASSED" : "FAILED");
  // assert( pass != 0 );
  printf("  ->OpenMP wall clock time: %f sec\n", cilk_time);


  // >>>    PTHREADS    <<<
 //  >>> IMPLEMENTATION <<<
//   >>>      HERE      <<<


  gettimeofday (&startwtime, NULL);
  parqsort(p_a, n,thread_num);
  gettimeofday (&endwtime, NULL);

  /* get time in seconds */
  par_thr_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
  + endwtime.tv_sec - startwtime.tv_sec);

  pass = test(p_a, n);
  // printf(" PTHREADS TEST %s\n",(pass) ? "PASSED" : "FAILED");
  assert( pass != 0 );
  printf("  ->PTHREADS wall clock time: %f sec\n", par_thr_time);

  /* >>>SEQUENTIAL<<<
     >>>   HERE   <<<
  sort elements in original order */

  gettimeofday (&startwtime, NULL);
  qsort_seq(a, n);
  gettimeofday (&endwtime, NULL);

  /* get time in seconds */
  seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
                      + endwtime.tv_sec - startwtime.tv_sec);

  /* validate result */
  pass = test(a, n);
  printf("SEQUENTIAL TEST %s\n",(pass) ? "PASSED" : "FAILED");
  // assert( pass != 0 );

    /* print sorted vector */
  /* print(a, n); */
  // printf("printing a and p_a after both sorts \n");
  // print(a,n);
  // print(p_a,n);
  // parqsort(p_a, n);


  /* print execution time */
  printf("  ->Sequential wall clock time: %f sec\n", seq_time);

  // >>>    STANDARD    <<<
 //  >>> IMPLEMENTATION <<<
//   >>>      HERE      <<<


  gettimeofday (&startwtime, NULL);
  qsort(std_a,n,sizeof(int),comparetor);
  gettimeofday (&endwtime, NULL);

  /* get time in seconds */
  std_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
  + endwtime.tv_sec - startwtime.tv_sec);

  pass = test(std_a, n);
  printf("STANDARD TEST %s\n",(pass) ? "PASSED" : "FAILED");
  assert( pass != 0 );
  printf("  ->STANDARD wall clock time: %f sec\n", std_time);


  /* EXIT */
  return 0;

}

/** -------------- SUB-PROCEDURES  ----------------- **/

/** procedure test() : verify sort results **/
int test(int *a, int n) {

  int pass = 1;
  for(int i=1;i<n;i++){
    if (a[i]<a[i-1]){
      pass=0;
      break;
    }
  }


  return pass;

}

/** procedure init() : initialize array "a" with data **/
void init(int *a, int n) {
  int i;
  srand(time(NULL));
  for (i = 0; i < n; i++) {
    a[i] = rand() % n; // (N - i);
  }
}

/** procedure  print() : print array elements **/
void print(int *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}


/** procedure  comparetor() : compare elements for qsort **/
int comparetor (const void * a, const void * b)
	{
		return ( *(int*)a - *(int*)b );
	}
