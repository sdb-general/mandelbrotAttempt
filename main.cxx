#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include "include/func.hpp"
#include "include/complex.hpp"

#include "boost/program_options.hpp"
using namespace boost::program_options;
SDL_Event event;

const int screenWidth = 1600;
const int screenHeight = 900;
const int screenBPP = 32;

// const double numWidth = 0.5;

// const std::pair<double, double> centre {-0.8,-0.2};

int main(int argc, const char *argv[])
{
  // add programme options
  variables_map vm;
  try
  {
    
    options_description desc{"Options"};
    desc.add_options()
      ("centrex", value<double>()->default_value(0), "CentreX")
      ("centrey", value<double>()->default_value(0), "CentreY")
      ("zoom", value<double>()->default_value(3), "Zoom" );

    
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << "\n";
    abort();
  }

  const double numWidth = vm["zoom"].as<double>();

  const std::pair<double, double> centre {
                                          vm["centrex"].as<double>(),
                                          vm["centrey"].as<double>()
                                          };

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
  SDL_SetRenderDrawColor(lRenderer, 86, 29, 94, 0xFF); 
  // SDL_SetRenderDrawColor(lRenderer, 0xFF, 0, 0, 255);
  // SDL_RenderClear(renderer);
  SDL_RenderPresent(lRenderer); //updates the window

  mandelDraw(lRenderer, screenWidth, screenHeight, numWidth, centre);

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