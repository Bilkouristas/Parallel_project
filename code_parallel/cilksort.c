#include <stdio.h>
#include <stdlib.h>
// #include <sys/time.h>
#include "qsort-sequential.h"
// #include <assert.h>
#include <pthread.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>

char str_workernum[12];
// void setWorkers(int n){
  // sprintf(str_workernum, "%d", n);
  // printf("workers are %d \n", n);
  // return str_workernum;
// }

void setWorkerz(char *n){
  __cilkrts_end_cilk();
  __cilkrts_set_param("nworkers", n);
}

int getWorkers(){
  return __cilkrts_get_nworkers();
}

int maxWorkers=0;
int initialength=0;

void cilk_qs(int *a,int n){
  int parallel=0;
  // int denom = (maxWorkers>16) ? 4 : maxWorkers;
  if(n>1){
    int p = partition(a,n);
    // // setWorkers(getWorkers());
    // if (getWorkers()-1<maxWorkers) {
    if(n>=(initialength/(maxWorkers*2))){ //maxWorkers
        parallel=1;
    }

    // }

    if (parallel) {
      cilk_spawn cilk_qs(a,p);
      cilk_qs(&a[p+1],n-p-1);
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

  // setWorkers(worker_num);
  // setWorkerz(str_workernum);
  // __cilkrts_end_cilk();
  // __cilkrts_set_param("nworkers", str_workernum);
  // setWorkers(getWorkers());

  cilk_spawn cilk_qs(a,n);
  cilk_sync;
}







// printf("derp\n");
