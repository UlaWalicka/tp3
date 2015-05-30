#include "timer.hpp"

Timer::Timer()
{
    start_time = 0;
    delta = 0;
}

void Timer::start()
{
    start_time = SDL_GetPerformanceCounter();
}

void Timer::measure()
{
    Uint64 current = SDL_GetPerformanceCounter();
    delta = current - start_time;
    start_time = current;
}

double Timer::getDelta()
{
    return (double)delta/SDL_GetPerformanceFrequency();
}
