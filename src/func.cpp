#include "../include/func.hpp"
#include <assert.h>
#include <chrono>
#include "../include/complex.hpp"

//threading
#include <thread>
#include <boost/asio.hpp>
#include <mutex>

const int Concurrency = std::thread::hardware_concurrency();
// const int Concurrency = 4;
std::mutex mutex;



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


StopWatch::StopWatch( std::string message="")
	{
	if (message == "") {std::cout << " beginning counter\n";}
	else {std::cout << " beginning " << message << std::endl; mMessage = message;}
	mStartTime = std::chrono::high_resolution_clock::now();
	}
StopWatch::~StopWatch()
	{
	std::cout << "\n Ending operation";
	if (mMessage!="") std::cout << " " << mMessage;
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - mStartTime);
	std::cout << ", time taken " << duration.count() << " milliseconds"<< std::endl;
	}

void lineRender(SDL_Renderer* aRenderer, std::vector<bool>& aMandel, int& aDisplacement) // vector of bools for if we should colour in or not
{
  mutex.lock();
  int lIter = 0;
  for (auto el : aMandel) 
  {
    if (el) SDL_RenderDrawPoint(aRenderer, aDisplacement, lIter);
    lIter++;
  //   std::cout << el << "\n";
  //   abort();
  }
  mutex.unlock();
}


void mandelDraw ( SDL_Renderer* aRenderer, const int aScreenWidth, const int aScreenHeight, const float numWidth)
{
  std::cout << "concurrency is " << Concurrency << "\n";

  float dW = numWidth / float(aScreenWidth), lW = -0.5 * numWidth; //local variable for width and its increment
  float dH = numWidth / float(aScreenHeight), lH = -0.5 * numWidth;

  std::vector<bool> lMandelHeightVect (aScreenHeight); //bool array for whether we have mandel or not

  /*
  my intention on the line below is to declare an empty object, like:
    int i;
  but i haven't worked out how to properly overload the constructor
  */
  Complex lComplex{0,0}; 
  for (int widthIter = 0; widthIter < aScreenWidth; widthIter++, lW += dW) 
  {
    
    lH = -0.5 * numWidth;
    for (int heightIter = 0; heightIter < aScreenHeight; heightIter++, lH += dH)
    {
      //construct complex number
      lComplex = Complex{lW, lH};
      // if ( isMandelBrot(lComplex) ) SDL_RenderDrawPoint(lRenderer, widthIter, heightIter);
      lMandelHeightVect[heightIter] = isMandelBrot(lComplex);
    }
    //render
    lineRender(aRenderer, lMandelHeightVect, widthIter);
  }

  SDL_RenderPresent(aRenderer);
}
