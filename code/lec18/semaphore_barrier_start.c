int remain =5; 
void barrier() { 
/* Rearrange the following */
   sem_wait(&s);
   sem_post(&s);
   remain --;
   pthread_mutex_lock(&m);
   pthread_mutex_unlock(&m);
   if(remain)   
}
