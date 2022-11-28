#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include "include/func.hpp"
#include "include/complex.hpp"
// http://lazyfoo.net/SDL_tutorials/lesson04/index.php

SDL_Event event;

const int screenWidth = 800;
const int screenHeight = 480;
const int screenBPP = 32;

int main()
{


  if(SDL_Init(SDL_INIT_VIDEO) != 0){
    std::cout << "couldn't init\n"; return 1;
  }
  SDL_Window* screen = SDL_CreateWindow("my application",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        screenWidth,screenHeight, 0);
  assert(screen);
  SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);
  assert(renderer);
  SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00); 
  // SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer); //updates the window

  drawCircle(renderer, 640/2, 480/2, 50);

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