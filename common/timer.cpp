#include "timer.h"

void Timer::start()
{
    startTime = std::clock();
}

double Timer::stop()
{
    return (( std::clock() - startTime ) / (double) CLOCKS_PER_SEC);
}
