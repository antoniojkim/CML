#ifndef __UTILS_TIMER_H__
#define __UTILS_TIMER_H__

#include <ctime>
#include <iostream>

class Timer {

    unsigned int lap = 0;
    unsigned int numLaps;

    std::clock_t start;

    public:
        Timer(unsigned int numLaps = 1): numLaps{numLaps}, start{clock()} {}

        ~Timer(){
            std::cout << "Took " << double(clock()-start)/CLOCKS_PER_SEC << " seconds" << std::endl;
        }

        void operator++(){
            lap += 1;
        }

        bool operator!(){
            return lap < numLaps;
        }
}

#define TIMEIT for(Timer t; !t; ++t)

#endif // __UTILS_TIMER_H__
