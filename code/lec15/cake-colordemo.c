#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define CONSUMER 

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

int cake = 0;
volatile int please_stop = 0;

void decrement() { // Will block if zero
  pthread_mutex_lock(&m);
  while(cake == 0) {
     printf("        cake_eater/decrement: cake is zero...  calling pthread_cond_wait\n");

     pthread_cond_wait(&cv, &m); // unlock mutex, SLEEP, later... lock mutex
     // SPURIOUS WAKEUP

     printf("        cake_eater/decrement: pthread_cond_wait returned (Is cake>0?)\n");
  }  
     printf("        cake_eater/decrement: -- ");

  cake --;
  pthread_mutex_unlock(&m);
}

void increment() {
  pthread_mutex_lock(&m);
    printf("        cake_maker/increment: ++ \n");
  cake ++;
  
    printf("        cake_maker/increment: pthread_cond_broadcast\n");
  pthread_cond_broadcast(&cv);  // Wake up all hungry sleeping cake eaters
  
    //or pthread_cond_signal(&cv);  // Wake up one hungry sleeping cake eater
  
  pthread_mutex_unlock(&m);
    
}

void* cake_eater(void*arg) {
  while(!please_stop) {
    sleep(1);
    decrement();
    printf("     \e[102;30mConsumer: Thanks! Now %d pieces left\e[49;39m\n",cake); 
  }
  return NULL;
}
void* cake_maker(void*arg) {
  while(!please_stop) {
    sleep(5);
    printf("     \e[103;30mProducer: Time for more cake\e[49;39m\n");
    sleep(1);
    increment();
    increment();
    increment();
  }
  return NULL;
  
}
void time_to_stop(int signal) {
  please_stop = 1;
}

int main() {
  signal(SIGINT, time_to_stop);
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, cake_eater, NULL);
  pthread_create(&tid2, NULL, cake_maker, NULL);
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  // reset display
  printf("\e[39;49m");
  return EXIT_SUCCESS;
}