#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void* myfunc(void*ptr) {
  int myvalue = * (int*) ptr;
  pthread_t myid = pthread_self();
  printf("My thread id is %p and I'm starting at %d\n",(void*) myid , myvalue);
  
  return NULL;
}

pthread_t tid[10]; 

int main() {
  // Each thread needs a different value of i 
  
  for(int i =0; i < 10; i++) {

     pthread_create( &tid[i], NULL, myfunc, &i);
  }
    
  pthread_exit(NULL) ; // this is a one way trip, pthread_exit never returns !!
  return 0;
}

