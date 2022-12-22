#include "../include/func.hpp"
#include <assert.h>
#include <chrono>
#include "../include/complex.hpp"

//threading
// #include <thread>
// #include <boost/asio.hpp>
// #include <mutex>

// const int Concurrency = std::thread::hardware_concurrency();
// const int Concurrency = 1;
// std::mutex mutex;
// boost::asio::thread_pool pool(Concurrency);


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



void blockRender(SDL_Renderer* aRenderer, std::vector<std::vector<bool>>& aScreen, const int aScreenWidth, const int aScreenHeight, double PIXELSCALEFACTOR)
{

  for (int w = 0 ; w < aScreenWidth; w ++)
    for (int h = 0; h < aScreenHeight; h ++)
    {
      // ensure correct scaling!
      if (aScreen[w / PIXELSCALEFACTOR][h / PIXELSCALEFACTOR]) SDL_RenderDrawPoint(aRenderer, w, h);
    }

}


// this function is where it all happens
void mandelDraw ( SDL_Renderer* aRenderer, const int aScreenWidth, const int aScreenHeight, const double PIXELSCALEFACTOR, const double numWidth, const std::pair<double, double> centre, const int aMaxIters)
{
  StopWatch s = StopWatch("Mandeldraw");
  
  //scaling the operation down by our pixel scale factor

  const int lScaledHeight = aScreenHeight / PIXELSCALEFACTOR + 1;
  const int lScaledWidth = aScreenWidth / PIXELSCALEFACTOR + 1; //trying to fix the end - of - array problem

  std::vector<std::vector<bool>> lScreen (
    lScaledWidth, std::vector<bool>(lScaledHeight) 
  );

  const double dW = numWidth / double(lScaledWidth) ;  //local variable for width and its increment
  const double dH = numWidth / double(lScaledHeight);


    
    
    

    //lambda starts here -----------------------------------------------------------------------------

  std::vector<bool> lMandelHeightVect (lScaledHeight);
  double lH;
  double lW = centre.first -0.5 * numWidth ;//+  dW * offset / Concurrency; //ensures correct starting point
  for (int widthIter = 0; widthIter < lScaledWidth; widthIter++, lW += dW)
    {
      lH = centre.second -0.5 * numWidth;
      for (int heightIter = 0; heightIter < lScaledHeight; heightIter++, lH += dH)
      {
        lScreen[widthIter][heightIter] =  isMandelBrot(lW, lH, aMaxIters);;
      }
    }

    //lambda ends here -------------------------------------------------------------------------------

      
    
  

  // pool.join();

  std::cout << " Rendering\n";

  blockRender(aRenderer, lScreen, aScreenWidth, aScreenHeight, PIXELSCALEFACTOR);
  SDL_RenderPresent(aRenderer);
}
