#ifndef __AUTOMODE__
#define __AUTOMODE__

#include "Task.h"

class AutoMode : public Task{
    
    float dNear, dFar;
    int potPin;

    public:
    
    AutoMode(float dNear, float dFar, int potPin);
    void tick();
    void init(int period);
    void shutDown();
};

#endif