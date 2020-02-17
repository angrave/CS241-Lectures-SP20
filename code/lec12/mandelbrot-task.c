#include <SDL2/SDL.h>
#include <complex.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

// ADD PTHREAD support (don't forget to compile with -pthread too)
#include <pthread.h>

// Run ../build_sdl2.sh to download and install SDL2 to ${HOME}/localinstall/
// Linux - 
// export LD_LIBRARY_PATH=${HOME}/localinstall/lib/
// clang sdl_mande-thread-task.c -lSDL2 -I ${HOME}/localinstall/include/ -L ${HOME}/localinstall/lib -pthread && ./a.out 512 512 2000

typedef struct _task_t {
  int start_x;
  int start_y;
  int end_x;
  int end_y;
} task_t;


// Global variables initialize to zero / NULL.
int width;
int height;
int max_iterations;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* framebuffer;

uint32_t* myPixels; 

int num_tasks;
task_t* tasks;

#define max_threads 2

int thread_count;
pthread_t thread_ids[max_threads];

/* The core of the Mandelbrot repeat z= z^2+c and see if z stays bounded (close to zero).
We can stop iterating once |z| exceeds 2, because all values >2 diverge.
*/
int mandelbrot(int x, int y) {
  double realVal = 2.5 * x / width - 1.6; 
  double imgVal =  2.5 * (height - y) / height - 1.25;
  
  double const complex c = realVal + I * imgVal;
  double complex z = 0;
  
  int iterations = 0;
  for( ; iterations < max_iterations && cabs(z)< 2 ; iterations++) {
    z = z * z + c;
  }
  // Convert the iteration count into the R G B bytes, using different multipliers
  return (cabs(z) < 2) ? 0xffffff : iterations * 0x81021;
}

void init_gui() {
	//SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
  SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
	framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, width, height);
  SDL_RaiseWindow(window);
  SDL_PumpEvents();
}
void close_gui_after_keypress() {
  SDL_Event event;
  while( SDL_WaitEvent(&event) && event.type != SDL_KEYDOWN && event.type != SDL_QUIT) {}

	SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void update_gui() {
  SDL_PumpEvents();
  SDL_UpdateTexture(framebuffer, NULL, myPixels, width * sizeof(uint32_t) );
  SDL_RenderCopy(renderer, framebuffer, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void parse_args(int argc, char**argv) {
  if(argc == 4) {
    sscanf(argv[1],"%d", & width);
    sscanf(argv[2],"%d", & height);
    sscanf(argv[3],"%d", & max_iterations);
  }
  if(width < 16|| height < 16  || max_iterations < 1
    || width >= 1<<15 || height >= 1<<15) {
    fprintf(stderr,"Usage: %s <width> <height> <max_iterations> e.g. 512 512 1000\n", argv[0]);
    exit(1);
  }
}

void quit(char*mesg) {
  perror(mesg);
  exit(1);
}

int min(int a, int b) {return a<b? a: b;}

void* calc_runner3(void* arg) {
  task_t* task = (task_t*) arg;
  //printf("x: %d %d y: %d %d\n", task->start_x,task->end_x,task->start_y,task->end_y);
  
  for(int x = task->start_x; x < task->end_x; x++) {
    for(int y = task->start_y; y < task->end_y; y++) {
      myPixels[x + y * width] = mandelbrot(x,y);
    }
  }
  return NULL;
}

/* Randomly shuffle the order of the tasks */
void  shuffle_tasks(task_t*tasks, int num_tasks) {
  task_t temp;
  for(int i=0;i<  num_tasks-1; i++) {
    memcpy(&temp, &tasks[i],sizeof(task_t));
    int j = i + (rand() % (num_tasks-i));
    memcpy(&tasks[i], &tasks[j],sizeof(task_t));
    memcpy(&tasks[j], &temp,sizeof(task_t));
  }
}

void make_tile_tasks() {
  
  int size = 64;
  // round up  (in case height or width is not divisible by size)
  num_tasks = ((height+size-1) / size) * ((width+size-1) / size);
  // For this problem we can calculate all of the concurrent tasks
  tasks = calloc(num_tasks , sizeof(task_t));

  int i = 0;
  for(int y = 0; y < height; y+= size){
    for(int x = 0; x < width; x+= size) {
      assert(i< num_tasks);
      tasks[i].start_x = x;
      tasks[i].start_y = y;
      tasks[i].end_x = min(x+size,width);
      tasks[i].end_y = min(y+size,height);
      i++;
    }
  }
  assert(i ==  num_tasks);
  shuffle_tasks(tasks, num_tasks);
}

void join_all_task_threads() {
  for(int i=0;i< thread_count;i++){
    pthread_join(thread_ids[i], NULL);
  }
  thread_count = 0;
}

void run_all_tiles_and_wait() {    
  for(int i= 0; i < num_tasks; i++) {
    int result = pthread_create( & thread_ids[thread_count++] , NULL, calc_runner3, tasks+i);
    if(result) quit("pthread_create failed");
    
    // Max threads running, or we've reached the last task?
    // If so then join on all threads that we created earlier.
    // What are the limitations of this approach? Can we do better?
    if(thread_count == max_threads || i+1 == num_tasks) {
      join_all_task_threads();
      update_gui();
    }
  }
}

int main(int argc, char**argv) {
  parse_args(argc, argv);
	init_gui();
  
  myPixels = calloc(width * height, sizeof(uint32_t));
  
  make_tile_tasks();
  
  run_all_tiles_and_wait(); 
  
  close_gui_after_keypress();
  
  free(myPixels);
  return 0;
}
