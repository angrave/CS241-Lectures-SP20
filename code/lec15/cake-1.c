#include <pthread.c>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t m = PTHREAD=MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

int  cake = 0;

// race conditions!
// ... but a stepping stone to adding condition variables

void decrement() { // Will block if zero
  
  while(cake == 0) {

      sleep(1)

  }  
  cake --;

}

void increment() {
    cake ++;
}
