#include <stdio.h>
#include <stdlib.h>
// #include <sys/time.h>
#include "qsort-sequential.h"
// #include <assert.h>
#include <pthread.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>

char str_workernum[12];
void setWorkers(int n){
  sprintf(str_workernum, "%d", n);
  // return str_workernum;
}

int getWorkers(){
  return __cilkrts_get_nworkers();
}

int maxWorkers=0;
int initialength=0;

void cilk_qs(int *a,int n){
  int parallel=0;
  // int currentWorkers=__cilkrts_get_nworkers();
  int denom = (maxWorkers>16) ? 16 : maxWorkers;
  if(n>1){
    int p = partition(a,n);
    if (getWorkers()<maxWorkers) {
      if(n>(initialength/denom)){
        parallel=1;
      }

    }

    if (parallel) {
      cilk_spawn cilk_qs(a,p);
      cilk_spawn cilk_qs(&a[p+1],n-p-1);
      cilk_sync;
    }else{
      cilk_qs(a,p);
      cilk_qs(&a[p+1],n-p-1);
    }

  }

}


void cilksort(int *a,int n, int worker_num){
  maxWorkers=worker_num;
  initialength=n;
  setWorkers(worker_num);
  __cilkrts_set_param("nworkers", str_workernum);
  cilk_spawn cilk_qs(a,n);
  cilk_sync;
}







// printf("derp\n");
