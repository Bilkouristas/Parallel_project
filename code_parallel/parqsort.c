#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "qsort-sequential.h"
#include <assert.h>


#include <pthread.h>


int activeThreads = 0, maxThreads = 256;
int initialen = 0 ; //initial lenth of array

pthread_attr_t attr;
pthread_mutex_t mux;

void *qsort_pthr(void *arg){
  pthread_t tid1, tid2;
  struct thread_data *thread_data = (struct thread_data *)arg;
  int parallel=0;
  int p;
  int denom=0;
  denom = (maxThreads>16) ? 16 : maxThreads; //variable denominator to compare array size with thread availability
  if(thread_data->len>1){
    p=partition(thread_data->array,thread_data->len);
    //create 2 sub-structures for the two halves of the argument
    struct thread_data thread_data1;
    struct thread_data thread_data2;
    thread_data1.array=thread_data->array;
    thread_data1.len=p;
    thread_data2.array=&thread_data->array[p+1];
    thread_data2.len=thread_data->len-p-1;

    if(activeThreads<maxThreads){ //check if there are more threads to spare
      if((thread_data->len)>initialen/denom){ //if the array is small enough, just do it (sequentially)
        parallel=1;
        pthread_mutex_lock(&mux);
        activeThreads+=2;
        pthread_mutex_unlock(&mux);
      }
    }
    if(parallel){ //if more threads to spare, create 2 more
      pthread_create(&tid1,&attr,qsort_pthr,(void *)&thread_data1);
      pthread_create(&tid2,&attr,qsort_pthr,(void *)&thread_data2);
      pthread_join(tid1,NULL);
      pthread_join(tid2,NULL);
      pthread_mutex_lock(&mux); //free up the 2 threads, update counter
      activeThreads=activeThreads-2;
      // printf("activeThreads=%d \n",activeThreads);
      pthread_mutex_unlock(&mux);

    }else{  //if the thread limit has been reached, continue sequentially till a thread frees up
      qsort_pthr((void *)&thread_data1);
      qsort_pthr((void *)&thread_data2);
    }

    }
  }

void parqsort(int *a,int n,int p){
  maxThreads = p;
  initialen = n;
  pthread_t tid;

  pthread_attr_init( &attr );
  pthread_mutex_init (&mux, NULL);

  struct thread_data thread_data;
  thread_data.array=a;
  thread_data.len=n;

  pthread_create(&tid,&attr,qsort_pthr,(void *)&thread_data);
  pthread_join(tid,NULL);

  // print(thread_data.array,thread_data.len);

  pthread_mutex_destroy (&mux);

}
