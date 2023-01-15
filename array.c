#include <stdio.h>
#include <stdlib.h>
#include "mythreads.h"

#define SIZE 1250

static int array[SIZE] = {0};
// declare array of locks
pthread_mutex_t arr_locks[SIZE];
// add any global declarations here
pthread_mutex_t lock;

// return a random index
unsigned int get_idx() {
  return(random()%(SIZE));
}

void *array_update(void *args) {
  print_thread_info();
  // fill in your the solution here to update the array 10000 times.
  // do not remove or modify any other lines of code in this function
  // add acquire lock
  // pthread_mutex_lock(&lock);
  // critical section
  for (int i=0; i<10000; i++) {
    unsigned int idx = get_idx();
    pthread_mutex_lock(&arr_locks[idx]);
    array[idx]++;
    pthread_mutex_unlock(&arr_locks[idx]); 
  }
  // unlock 
  // pthread_mutex_unlock(&lock); 

  printf("%ld done\n",Thread_gettid());
  return NULL;
}

int main (int argc, char **argv)
{
  pthread_t threads[4];
  
  srandom(2001); // seed the random number generator
  my_threads_init();

  // fill in this portion to initialize locks and create 4 threads 
  // main should use join to wait for all four threads to finish before executing the finish up code
  pthread_mutex_init(&lock, NULL);

  for (int i=0; i<4; i++) {
    pthread_create(&threads[i], NULL, array_update, NULL);
    pthread_join(threads[i], NULL); 
  }

  my_threads_end();
  // main finish up code.
  int sum = 0;
  for (int i =0; i < SIZE; i++) {
    if (array[i]) {
      printf("%d: %d\n",i,array[i]);
      sum += array[i];
    }
  }
  printf("main: result %d\n",sum);

  return(0);
}
