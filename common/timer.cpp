#include "timer.h"

#define S_TO_MS 1000;

#include <iostream>

void Timer::start()
{
    startTime = clock();
}

void Timer::stop(double& time)
{
    time = ((std::clock() - startTime)/ (double) CLOCKS_PER_SEC) * S_TO_MS;
}
