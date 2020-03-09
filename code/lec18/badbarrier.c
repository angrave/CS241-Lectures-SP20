 void badbarrier() {
     pthread_mutex_lock(&m)
     count ++
     pthread_mutex_unlock(&m)

     // No memory fence - might never read a value of count that is updated by remote thread
     while(count != N) {
       pthread_yield();
     }

 }