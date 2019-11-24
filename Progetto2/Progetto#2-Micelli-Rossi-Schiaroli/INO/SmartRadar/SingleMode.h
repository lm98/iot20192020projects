#ifndef __SINGLEMODE__
#define __SINGLEMODE__

#include "Task.h"

class SingleMode : public Task{

    int pirPin;
    int potPin;

    public:
    SingleMode(int pirPin, int potPin);
    void tick();
    void init(int period);
    void shutDown();
};

#endif 
