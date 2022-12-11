#include "../include/func.hpp"
#include <assert.h>
#include <chrono>
#include "../include/complex.hpp"

//threading
#include <thread>
#include <boost/asio.hpp>
#include <mutex>

const int Concurrency = std::thread::hardware_concurrency();
// const int Concurrency = 1;
std::mutex mutex;
boost::asio::thread_pool pool(Concurrency);


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
  std::cout << "+-----------------+\n";
	if (message == "") {std::cout << " Beginning counter\n";}
	else {std::cout << " Beginning " << message << std::endl; mMessage = message;}
  std::cout << "+-----------------+\n";
	mStartTime = std::chrono::high_resolution_clock::now();
	}
StopWatch::~StopWatch()
	{
  std::cout << "+-----------------+\n";
	std::cout << " Ending operation ";
	if (mMessage!="") std::cout << mMessage;
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - mStartTime);
	std::cout << ", time taken " << duration.count() << " milliseconds"<< std::endl;
  std::cout << "+-----------------+\n";
	}

void lineRender(SDL_Renderer* aRenderer, std::vector<bool>& aMandel, int& aDisplacement) // vector of bools for if we should colour in or not
{
  mutex.lock();
  int lIter = 0;
  for (auto el : aMandel) 
  {
    if (el) SDL_RenderDrawPoint(aRenderer, aDisplacement, lIter);
    lIter++;
  }
  SDL_RenderPresent(aRenderer);
  mutex.unlock();
}

void blockRender(SDL_Renderer* aRenderer, std::vector<std::vector<bool>>& aScreen, const int aScreenWidth, const int aScreenHeight, int PIXELSCALEFACTOR)
{
  for (int w = 0 ; w < aScreenWidth; w ++)
    for (int h = 0; h < aScreenHeight; h ++)
    {
      //scale back up!
      if (aScreen[w / PIXELSCALEFACTOR][h / PIXELSCALEFACTOR]) SDL_RenderDrawPoint(aRenderer, w, h);
    }

}


// this function is where it all happens
void mandelDraw ( SDL_Renderer* aRenderer, const int aScreenWidth, const int aScreenHeight, const int PIXELSCALEFACTOR, const double numWidth, const std::pair<double, double> centre)
{
  StopWatch s = StopWatch("Mandeldraw");
  
  //scaling the operation down by our pixel scale factor

  const int lScaledHeight = aScreenHeight / PIXELSCALEFACTOR;
  const int lScaledWidth = aScreenWidth / PIXELSCALEFACTOR;

  std::vector<std::vector<bool>> lScreen (
    lScaledWidth, std::vector<bool>(lScaledHeight) 
  );



  const double dW = Concurrency * numWidth / double(lScaledWidth) ;  //local variable for width and its increment
  const double dH = numWidth / double(lScaledHeight);

  for (int offset = 0; offset < Concurrency; offset++)
  // the below will be posted into the threadpool
  {
    boost::asio::post( pool, [&, offset](){
    // let's do it 
      // Complex lComplex{0,0};
      std::cout << offset << "\n";
      std::vector<bool> lMandelHeightVect (lScaledHeight);
      double lH;
      double lW = centre.first -0.5 * numWidth +  dW * offset / Concurrency; //ensures correct starting point
      for (int widthIter = offset; widthIter < lScaledWidth; widthIter += Concurrency, lW += dW)
        {
          lH = centre.second -0.5 * numWidth;
          for (int heightIter = 0; heightIter < lScaledHeight; heightIter++, lH += dH)
          {
            lScreen[widthIter][heightIter] =  isMandelBrot(Complex{lW, lH});;
          }
        };
      }
    );
  }

  pool.join();

  std::cout << " Rendering\n";

  blockRender(aRenderer, lScreen, aScreenWidth, aScreenHeight, PIXELSCALEFACTOR);
  SDL_RenderPresent(aRenderer);
}
