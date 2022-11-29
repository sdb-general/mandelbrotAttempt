#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include "include/func.hpp"
#include "include/complex.hpp"

SDL_Event event;

const int screenWidth = 1900;
const int screenHeight = 1000;
const int screenBPP = 32;

const double numWidth = 3;

int main()
{
  // includeFunction();
  if(SDL_Init(SDL_INIT_VIDEO) != 0){
    std::cout << "couldn't init\n"; return 1;
  }
  SDL_Window* screen = SDL_CreateWindow("mandelbrot",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        screenWidth,screenHeight, 0);
  assert(screen);
  SDL_Renderer* lRenderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);
  assert(lRenderer);
  // SDL_SetRenderDrawColor(lRenderer, 0x00, 0xFF, 0x00, 0x00); 
  SDL_SetRenderDrawColor(lRenderer, 0xFF, 0, 0, 255);
  // SDL_RenderClear(renderer);
  SDL_RenderPresent(lRenderer); //updates the window

  mandelDraw(lRenderer, screenWidth, screenHeight, numWidth);

  bool quit = false;
  while (quit == false){
    while( SDL_PollEvent(&event) )
    {
      if (event.type == SDL_QUIT) quit = true;
    }
  }
  
  SDL_DestroyWindow(screen);
  SDL_Quit();
  return 0;
}