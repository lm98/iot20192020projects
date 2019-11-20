#ifndef __SINGLEMODE__
#define __SINGLEMODE__

#include "Task.h"

class SingleMode : public Task{

    public:
    void tick();
    void init(int period);
    
};

#endif 
