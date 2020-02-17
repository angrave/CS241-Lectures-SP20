#include <SDL2/SDL.h>
#include <complex.h>
#include <stdlib.h>
// ../build_sdl2.sh to download and install SDL2
// Linux - 
// export LD_LIBRARY_PATH=${HOME}/localinstall/lib/
// clang sdl_test.c -lSDL2 -I ${HOME}/localinstall/include/ -L ${HOME}/localinstall/lib && ./a.out

#define width 1024
#define height 1024

SDL_Window* window;
SDL_Renderer* renderer;


int main()
{
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
//	SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
	SDL_Texture* framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, width, height);
  
  uint32_t myPixels[ width * height ];
  
  for(int y=0; y < height; y++) {
    for(int x=0; x < width; x++) {
       myPixels[x + y * width] =  - x * y;
    }
  }

	SDL_UpdateTexture(framebuffer, NULL, myPixels, width * sizeof(uint32_t) );
	SDL_RenderCopy(renderer, framebuffer, NULL, NULL);
	SDL_RenderPresent(renderer);
  
  SDL_Event event;
  do SDL_WaitEvent(&event); while(event.type != SDL_KEYDOWN);

	SDL_DestroyWindow(window);
	SDL_Quit();
}
