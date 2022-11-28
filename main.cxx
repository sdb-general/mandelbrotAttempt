#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include "include/func.hpp"
#include "include/complex.hpp"

SDL_Event event;

const int screenWidth = 1600;
const int screenHeight = 900;
const int screenBPP = 32;

const float numWidth = 3;

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
  SDL_Renderer* lRenderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);
  assert(lRenderer);
  // SDL_SetRenderDrawColor(lRenderer, 0x00, 0xFF, 0x00, 0x00); 
  SDL_SetRenderDrawColor(lRenderer, 0xFF, 0, 0, 255);
  // SDL_RenderClear(renderer);
  SDL_RenderPresent(lRenderer); //updates the window

  float dW = numWidth / float(screenWidth), lW = -0.5 * numWidth; //local variable for width and its increment
  float dH = numWidth / float(screenHeight), lH = -0.5 * numWidth;

  /*
  my intention on the line below is to declare an empty object, like:
    int i;
  but i haven't worked out how to properly overload the constructor
  */
  Complex lComplex{0,0}; 
  for (int widthIter = 0; widthIter < screenWidth; widthIter++, lW += dW) 
  {
    lH = -0.5 * numWidth;
    for (int heightIter = 0; heightIter < screenHeight; heightIter++, lH += dH)
    {
      //construct complex number
      lComplex = Complex{lW, lH};
      if ( isMandelBrot(lComplex) ) SDL_RenderDrawPoint(lRenderer, widthIter, heightIter);
    }
  }

  SDL_RenderPresent(lRenderer);

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