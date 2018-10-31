#include <stdio.h>
#include <stdlib.h>
// #include <sys/time.h>
#include "qsort-sequential.h"
// #include <assert.h>
#include <pthread.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "omp.h"


int maxOpenThreads=0;
int initialOpenLength=0;
int currentOpenThreads=0;
omp_lock_t lock;


void omp_qs(int *a,int n){
  int parallel=0;
  // int currentWorkers=__cilkrts_get_nworkers();
  int denom = (maxOpenThreads>16) ? 16 : maxOpenThreads;
  if(n>1){
    int p = partition(a,n);
    if (currentOpenThreads<maxOpenThreads) {
      if(n>(initialOpenLength/denom)){
        parallel=1;
        omp_set_lock(&lock);
        currentOpenThreads+=2;
        omp_unset_lock(&lock);
      }

    }

    if (parallel) {
      #pragma omp parallel sections
      {
        #pragma omp section
        {
          omp_qs(a,p);
        }
        #pragma omp section
        {
          omp_qs(&a[p+1],n-p-1);
        }
      }
    }else{
      omp_qs(a,p);
      omp_qs(&a[p+1],n-p-1);
    }

  }

}


void omp_qsort(int *a,int n, int openThreads_num){
  initialOpenLength=n;
  maxOpenThreads=openThreads_num;
  omp_init_lock(&lock);
  omp_qs(a,n);
  omp_destroy_lock(&lock);
}







// printf("derp\n");
