#ifndef __AUTOMODE__
#define __AUTOMODE__

#include "Task.h"

class AutoMode : public Task{
    
    public:
    
    void tick();
    void init(int period);
    void shutDown();
};

#endif