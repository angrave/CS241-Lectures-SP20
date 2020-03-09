
task_t* buffer[16];

sem_t numspaces, numitems;

init() {
  sem_init( &numspaces ,0/*pshared*/, 16);
  sem_init( &numspaces ,0/*pshared*/ , 0); 
}
int in, out;

void enqueue(value) {
  sem_wait( &numspaces);
  pthread_mutex_lock(&m);
  buffer[ (in++) & 0xf ] = value
  pthread_mutex_unlock(&m);  
  sem_post( &numitems);
}

task_t dequeue() {
  sem_wait(&numitems);
  pthread_mutex_lock(&m2);
  result = buffer[ (out++) & 0xf ]
  pthread_mutex_unlock(&m2);   
  sem_post(&numspaces); 
  return result; 
}