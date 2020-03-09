#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int game_running;
int jar = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv1 = PTHREAD_COND_INITIALIZER;
// Demo : cookie value still goes negative when we quit

void* cookie_eater(void*arg) {
 char*name = (char*) arg;
 while(game_running) {
   pthread_mutex_lock(&m);
   
   while(jar == 0 && game_running) { 
     printf("%s: \"No cookies! Going for a nap...\"\n", name);
     pthread_cond_wait( &cv1, &m);
     printf("%s has woken up!\n", name);
   }
   if(!game_running) {
     break;
   }
   jar --;
   int currentJar = jar;
   pthread_mutex_unlock(&m);
   printf("%s eats! %d cookie(s) remain\n",name,currentJar);
  } //while game_running
  pthread_mutex_unlock(&m);
  printf("%s finished\n",name);
  return NULL;
}

void add_cookie(int add) {
  pthread_mutex_lock(&m);
  jar += add;
  pthread_cond_broadcast(&cv1);
  pthread_mutex_unlock(&m);
}

int main() {
  game_running = 1;
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, cookie_eater, "Angrave");
  pthread_create(&tid2, NULL, cookie_eater, "Smith");
  puts("Number of cookies to add to the jar? (9=exit)");
  
  int add = 0;
  while( scanf("%d", &add) == 1 && add != 9) add_cookie(add);

  puts("Finishing...");
  pthread_mutex_lock(&m); // ensure memory fence --why you pay me the big $$
  game_running = 0;
  pthread_cond_broadcast(&cv1);
  pthread_mutex_unlock(&m);
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  
  puts("Finished!");
  exit(0);
}
