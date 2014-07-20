#ifndef TIMER_H
#define TIMER_H

#include <cstdio>
#include <ctime>

class Timer{

public:
    void start();
    void stop(double& time);

private:
    std::clock_t startTime;
};

#endif //TIMER_H
