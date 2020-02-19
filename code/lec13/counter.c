#include <pthread.h>
#include <stdio.h>

pthread_mutex_t duck  = PTHREAD_MUTEX_INITIALIZER;

int counter;

void* myfunc1(void*param) {
     int i=0; // stack variable
     for(; i < 1000000;i++)
        counter++; 
     return NULL;
}

void* myfunc2(void*param) {
     int i=0; // stack variable
     pthread_mutex_lock(&duck);
     for(; i < 1000000;i++)
        counter++;
     pthread_mutex_unlock(&duck); 
     return NULL;
}

void* myfunc3(void*param) {
     int i=0; // stack variable
     
     for(; i < 1000000;i++) {
       pthread_mutex_lock(&duck);
       counter++;
       pthread_mutex_unlock(&duck); 
     }
     return NULL;
}
pthread_t tid1, tid2;

int main() {
      pthread_create(&tid1, 0, myfunc3, NULL);
      pthread_create(&tid2, 0, myfunc3, NULL);

      pthread_join(tid2,NULL); // will block until thread 2 finishes
      pthread_join(tid1,NULL); // will block until thread 1 finishes
      
      printf("%d\n", counter );
      return 0;
}
