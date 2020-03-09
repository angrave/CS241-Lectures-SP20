#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

int  cake = 0; // is only manipulated by the two functions below

void decrement() { // Will block if zero
  pthread_mutex_lock(&m);
  
  while(cake == 0) {
      pthread_cond_wait(&cv, &m); // unlock mutex, SLEEP, later... lock mutex
  }
    
  cake --;
  
  pthread_mutex_unlock(&m);
}

void increment() { // never blocks
  pthread_mutex_lock(&m);
  
    cake ++;
    pthread_cond_broadcast(&cv);  // You could wake up all hungry sleeping cake eaters
    // pthread_cond_signal(&cv);  // You could wake up one hungry sleeping cake eater
  
  pthread_mutex_unlock(&m);
    
}
