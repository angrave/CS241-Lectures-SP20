int remain =5; 
.. sem_init(&s, 0, 0/*No Pizza slices!*/);

void barrier() { 
/* Rearrange the following */
  pthread_mutex_lock(&m);
  remain --;
  pthread_mutex_unlock(&m);
  
  if(remain) {
   sem_wait(&s); /* Will block */
  }
  // sem_post is initially called by 5th thread, that let's one thread to continue
  
  // so one thread escapes sem_wait, but then calls sem_post, so like dominoes they escape!
  sem_post(&s); // allows anotherone to continue

}
