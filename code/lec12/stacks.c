#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#include <pthread.h>
// compile with -pthread

void recurse(int param) {
  int calc= 10;
  calc ++;
  printf("calc=%d.  &calc = %p\n",calc, & calc);
  if(param >1) recurse(param-1);
}
void* thread_starts_here(void* ptr) {
  recurse(3);
  return NULL;
}
 
// Number of threads:
#define N (3)

int main() {
  
  pthread_t tids[N];
  for(int i=0;i<N;i++) {
    puts("Starting new thread...");
    pthread_create( & tids[i], NULL,thread_starts_here, NULL); 
    sleep(2);
    // uncomment this to get a surprise
    //pthread_join(tids[i],NULL);
  }
  pthread_exit(NULL); // No more code executed by this thread

  puts("The answer to life, universe, everything...");
  return 42; //we will never know
}
