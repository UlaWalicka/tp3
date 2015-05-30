#ifndef __TIMER_HPP
#define __TIMER_HPP

#include <SDL.h>

class Timer
{
    Uint64 start_time;
    Uint64 delta;

    public:
    Timer();

    void start();
    void measure();
    double getDelta();
};

#endif
