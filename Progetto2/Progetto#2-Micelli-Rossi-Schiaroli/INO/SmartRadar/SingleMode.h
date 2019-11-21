#ifndef __SINGLEMODE__
#define __SINGLEMODE__

#include "Task.h"

class SingleMode : public Task{

    int pirPin;

    public:
    SingleMode(int pirPin);
    void tick();
    void init(int period);
    void shutDown();
};

#endif 
