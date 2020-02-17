#include <pthread.h>
#include <stdio.h>

void* valentines(void* param) {
  printf("%s", param);
  fflush(stdout);
  return NULL;
}

int main() {
  pthread_t tids[2]; 
  pthread_create( tids, NULL, valentines, "Hello ");
  pthread_create( tids +1, NULL, valentines, "World");

  pthread_exit(NULL);
  
}