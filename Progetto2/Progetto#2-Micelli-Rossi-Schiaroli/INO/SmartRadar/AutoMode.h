#ifndef __AUTOMODE__
#define __AUTOMODE__

#include "Task.h"

class AutoMode : public Task{
    
    float dNear, dFar;

    public:
    
    AutoMode(float dNear, float dFar);
    void tick();
    void init(int period);
    void shutDown();
};

#endif