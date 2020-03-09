#include <stdio.h>
#include <pthread.h>

pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int fireworks=0;
pthread_t tids[5];
void* firework(void*); // defined later in this file

int main(int argc,char** argv) {
  for(int i=0;i<5;i++)  pthread_create( tids+i , NULL, firework, NULL);
  fireworks = 1;
  pthread_cond_signal(&cv);
  pthread_exit(NULL); // wait for all threads to finish
  return 0;
}
void* firework(void*param) {
  pthread_mutex_lock(&m);
  while(fireworks ==0)  {pthread_cond_wait(&cv, &m); }
  pthread_cond_broadcast(&cv);
  fireworks ++;
  printf("Oooh ahh %d\n", fireworks);
  fireworks --;  
  pthread_mutex_unlock(&m);
  return NULL;
}
