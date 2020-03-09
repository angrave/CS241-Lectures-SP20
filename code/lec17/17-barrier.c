
int counter = 0;

void barrier() {
  pthread_mutex_lock(&m);
  counter ++;
  if(counter == 8) {
    pthread_cond_broadcast(&cv);
  }
  
  while( counter < 8) { 
    pthread_cond_wait(&cv,&m);
  }
  pthread_mutex_unlock(&m);  
}
