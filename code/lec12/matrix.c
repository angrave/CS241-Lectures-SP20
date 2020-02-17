#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#include <pthread.h>
// compile with -pthread


// Number of threads:
#define N (10)

pthread_t tid_runners[N];
pthread_t tid_display;
int width;
int height;

void* display(void* ptr) {
  while(1) {
    for(int y=0; y < height;y++) {
      write( 1, ptr +  y * width, width);
      write( 1, "\n", 1);
    }
    // Move back up by height lines then sleep for 10 milliseconds
    for(int y=0; y < height; y++) write(1,"\033[1A",5);
    usleep(10000);
  }
  return NULL;
}
 
void* run(void* ptr) {
   char* image = ptr;
   
   while(1) {
      int x= rand() % width;
      char*mesg = "CS241 Rocks!";
      char c = mesg[ rand() % strlen(mesg) ];
      for(int y = 0 ; y < height && (rand() & 15); y ++) {
          image[ x + y*width ] =c; //^= 0x6E; // flip some bits
          usleep(x * 500L);
      }
      
    }
    return NULL;
}
  
void getTerminalWidthHeight(int* width, int* height) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *width = w.ws_col;
    *height = w.ws_row;
}
 
int main() {
  puts("\x1b[32m\x1b[2J"); // Green text and clear screen. use 'reset' to reset terminal
  getTerminalWidthHeight(&width, &height);
  
  void* image = malloc(height * width);
  memset(image, '.' , height * width);
 
  pthread_create(&tid_display,NULL,display, image);

  for(int i=0;i<N;i++) {
    pthread_create(tid_runners+i,NULL,run, image); 
  }
  pthread_exit(NULL); // No more code executed by this thread
  return 42; // so we will never know the answer to life, universe, everything.
}