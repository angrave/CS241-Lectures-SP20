#include <pthread.h>
#include <stdio.h>

pthread_mutex_t duck = PTHREAD_MUTEX_INITIALIZER;

int sharedcounter=0;

void* myfunc1(void*param) {
     int i=0; // stack variable

     for(; i < 1000000;i++) {
          sharedcounter++;
     }
     return NULL;
}

pthread_t tid1, tid2;

int main() {
      pthread_create(&tid1, 0, myfunc1, NULL);      
      pthread_create(&tid2, 0, myfunc1, NULL);

      pthread_join(tid1,NULL); // will block until thread finishes

      pthread_join(tid2,NULL); // will block until thread finishes
      
      printf("%d\n", sharedcounter );
      return 0;
}
