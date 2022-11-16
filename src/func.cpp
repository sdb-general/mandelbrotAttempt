#include "../include/func.hpp"
#include <assert.h>

void includeFunction(){
  std::cout << "printing inside included function\n";
}

void drawCircle(SDL_Renderer* aRenderer, int32_t aX, int32_t aY, int32_t aR){
  assert(aRenderer);
  SDL_SetRenderDrawColor(aRenderer, 0xFF, 0, 0, 255);
  const int32_t lDiam = 2 * aR;
  int32_t x = (aR - 1);
  int32_t y = 0;
  int32_t tx = 1;
  int32_t ty = 1;
  int32_t error = (tx - lDiam);
  while (x >= y)
  {
    //  Each of the following renders an octant of the circle
    SDL_RenderDrawPoint(aRenderer, aX + x, aY - y);
    SDL_RenderDrawPoint(aRenderer, aX + x, aY + y);
    SDL_RenderDrawPoint(aRenderer, aX - x, aY - y);
    SDL_RenderDrawPoint(aRenderer, aX - x, aY + y);
    SDL_RenderDrawPoint(aRenderer, aX + y, aY - x);
    SDL_RenderDrawPoint(aRenderer, aX + y, aY + x);
    SDL_RenderDrawPoint(aRenderer, aX - y, aY - x);
    SDL_RenderDrawPoint(aRenderer, aX - y, aY + x);

    if (error <= 0)
    {
      ++y;
      error += ty;
      ty += 2;
    }

    if (error > 0)
    {
      --x;
      tx += 2;
      error += (tx - lDiam);
    }
  }
  SDL_RenderPresent(aRenderer);
}
