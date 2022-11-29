#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <chrono>


void includeFunction();

void drawCircle(SDL_Renderer* aRenderer, int32_t aX, int32_t aY, int32_t aR);

struct StopWatch
{
	StopWatch( std::string message );

	std::chrono::high_resolution_clock::time_point mStartTime;
	std::string mMessage;
	
	virtual ~StopWatch(); 
};

void lineRender(SDL_Renderer* aRenderer, std::vector<bool>& aMandel, int& aDisplacement);

void mandelDraw ( SDL_Renderer* aRenderer, const int aScreenWidth, const int aScreenHeight, const double numWidth);
