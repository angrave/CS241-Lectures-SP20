#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static char message[200];
int pleaseStop;

pthread_mutex_t duck = PTHREAD_MUTEX_INITIALIZER;

char* toTextMessage(char*to, char* from, int val) {
	  sprintf(message,"Text:%s From:%s You won %d million",to, from, val);
	  return message;
}

void* runner2(void* ptr) {
  while(!pleaseStop) {
//    pthread_mutex_lock(&duck);
    char * unused = toTextMessage("JurassicPark","Dinosaur",999);
//    pthread_mutex_unlock(&duck);
  }
  return NULL;
}

void* runner1(void* ptr) {
  int count = 0;
  while(!pleaseStop) {
 //   pthread_mutex_lock(&duck);
    
    char* mesg = toTextMessage("angrave","illinois",1);

	  printf("%6d Sending %s\n", count ++, mesg); 
 //   pthread_mutex_unlock(&duck);
  }
  return NULL;
}




int main() {
   pthread_t tid1, tid2;
	 pthread_create(&tid1, 0, runner1, NULL);
   sleep(2);
	 pthread_create(&tid2, 0, runner2, NULL);
	 sleep(5);
	 pleaseStop = 1;
	 pthread_join(tid1, NULL);
	 pthread_join(tid2, NULL);
}
