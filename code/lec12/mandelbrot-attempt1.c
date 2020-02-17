#include <SDL2/SDL.h>
#include <complex.h>
#include <stdlib.h>

// ADD PTHREAD support (don't forget to compile with -pthread too)
#include <pthread.h>

// Run ../build_sdl2.sh to download and install SDL2 to ${HOME}/localinstall/
// Linux - 
// export LD_LIBRARY_PATH=${HOME}/localinstall/lib/
// clang sdl_mande-thread-v1l.c -lSDL2 -I ${HOME}/localinstall/include/ -L ${HOME}/localinstall/lib -pthread && ./a.out

// Global variables initialize to zero / NULL.
int width;
int height;
int max_iterations;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* framebuffer;

uint32_t* myPixels; 

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
int check_for_keypress() {
  SDL_Event event;
  return (SDL_PollEvent(&event) && (event.type == SDL_KEYDOWN || event.type == SDL_QUIT));
}

void wait_keypress() {
  SDL_Event event;
  while( SDL_WaitEvent(&event) && event.type != SDL_KEYDOWN && event.type != SDL_QUIT) {}
}

void close_gui() {
	SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void update_gui() {
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

/*
Let's just create 1000 of threads! (one per row). hey it seems to work on my machine. Not so much on linux-a2
*/

void* calc_runner1(void*badhack1) {
  // Hey compiler treat this address as a plain integer
  
  int y = (int)badhack1; //We are NOT derefencing this pointer 
  for(int x=0; x < width; x++) {
    myPixels[x + y * width] = mandelbrot(x,y);
  }
  return NULL;
}


int main(int argc, char**argv) {
  parse_args(argc, argv);
	init_gui();
  
  myPixels = calloc(width * height, sizeof(uint32_t));
  
  pthread_t* tids = calloc(height, sizeof(pthread_t));
  
  for(int y = 0; y < height; y++) {
      void* badhack = (void*) y; // Hey compiler! Treat this integer as a memory address!
    
      int result = pthread_create( & tids[y] , NULL, calc_runner1, badhack);
      if(result) quit("pthread_create failed");
  }
  
  while( ! check_for_keypress()) {
    update_gui();
    SDL_Delay(10);
  }
  
  close_gui();
  free(myPixels);
  return 0;
}
