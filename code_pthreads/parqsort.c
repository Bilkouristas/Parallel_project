#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "qsort-sequential.h"
#include <assert.h>


#include <pthread.h>


// void print(int *a, int n) {
//   int i;
//   for (i = 0; i < n; i++) {
//     printf("%d ", a[i]);
//   }
//   printf("\n");
// }
int activeThreads = 0, maxThreads = 256;

pthread_attr_t attr;
pthread_mutex_t mux;

void *qsort_pthr(void *arg){
  pthread_t tid1, tid2;
  struct thread_data *thread_data = (struct thread_data *)arg;
  int parallel=0;
  int p;
  if(thread_data->len>1){
    p=partition(thread_data->array,thread_data->len);
    struct thread_data thread_data1;
    struct thread_data thread_data2;
    thread_data1.array=thread_data->array;
    thread_data1.len=p;
    thread_data2.array=&thread_data->array[p+1];
    thread_data2.len=thread_data->len-p-1;

    if(activeThreads<maxThreads){
      if(thread_data->len>2^14){
      parallel=1;
      pthread_mutex_lock(&mux);
      activeThreads+=2;
      // printf("activeThreads=%d  length=%d \n",activeThreads,thread_data->len);
      pthread_mutex_unlock(&mux);
    }

    }
    // if(thread_data->len<2^14){ //if the array is small enough, just do it
    //   parallel=0;
    // }
    if(parallel){
      // struct thread_data thread_data1;
      // struct thread_data thread_data2;
      // thread_data1.array=thread_data.array;
      // thread_data1.len=p;
      // thread_data2.array=&thread_data.array[p+1];
      // thread_data1.len=thread_data1.len-p-1;

      pthread_create(&tid1,&attr,qsort_pthr,(void *)&thread_data1);
      pthread_create(&tid2,&attr,qsort_pthr,(void *)&thread_data2);
      pthread_join(tid1,NULL);
      pthread_join(tid2,NULL);
      pthread_mutex_lock(&mux);
      activeThreads=activeThreads-2;
      // printf("activeThreads=%d \n",activeThreads);
      pthread_mutex_unlock(&mux);

    }else{
      qsort_pthr((void *)&thread_data1);
      qsort_pthr((void *)&thread_data2);
    }

    }
  }

void parqsort(int *a,int n,int p){
  maxThreads = p;
  // activeThreads=2;
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
