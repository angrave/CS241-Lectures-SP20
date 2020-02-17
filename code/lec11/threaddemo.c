#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* hello(void*arg) {
  sleep(1);
  char* mesg = arg;
  printf("My mesg is at %p\n", &mesg);
  printf("hello %s!\n", mesg);
  
  if( mesg[0] == 'T') {
    pthread_exit((void*) 0xdeadc0de); // nothing happens after this
  }
  
  return (void*) 0xdeadbeef;
}

int main(int argc, char**argv) {
  void *ptr = "Banana";
  pthread_t tid1, tid2;
  printf("Address of tid1 is %p\n", & tid1);
  
  pthread_create( &tid1, NULL, hello, ptr );
  pthread_create( &tid2, NULL, hello, "Tomato" );
  void* retValue1;
  void* retValue2;
  pthread_join( tid1,& retValue1);
  pthread_join( tid2,& retValue2); 
  
  printf("retValue1 is %p\n", retValue1) ;
  printf("retValue2 is %p\n", retValue2) ;
  
  return EXIT_SUCCESS;
}