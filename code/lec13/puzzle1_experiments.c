#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define N 5
int starting_value[N];
pthread_t tid[N]; 

void* myfunc(void*ptr) {
  int myvalue = * (int*) ptr;
  printf("My thread id is %p and I'm starting at %d\n",pthread_self(), myvalue);

  return NULL;
}
int main() {
  puts("Experiment 1: pthread_create( &tid[i], 0, myfunc, & i )");
  
  for(int i =0; i < N; i++) {
     pthread_create( &tid[i],NULL, myfunc, & i );
  }
  
  for(int i =0; i < N; i++) {
    pthread_join(tid[i],NULL);
  }
  
  puts("Experiment 2: pthread_create(&tid[i],NULL, myfunc, & starting_value[i] );");
  
  for(int i =0; i < N; i++) {
     starting_value[i] = 200 + i;
     pthread_create(&tid[i],NULL, myfunc, & starting_value[i] );
  }
  for(int i =0; i < N; i++) {
    pthread_join(tid[i],NULL);
  }
  
  puts("Experiment 3: pthread_create & immediately pthread_create");
  
  for(int i =0; i < N; i++) {
    starting_value[i] = 300 + i;
    pthread_create( &tid[i],NULL, myfunc, & starting_value[i] );
    pthread_join(tid[i],NULL);
  }
  
  pthread_exit(NULL) ; // this is a one way trip - never returns !!!!!!!!!
  return 0;
}

