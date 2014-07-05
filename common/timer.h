#ifndef TIMER_H
#define TIMER_H

#include <cstdio>
#include <ctime>

class Timer{

public:
    void start();
    double stop();

private:
    std::clock_t startTime;
};

#endif //TIMER_H
