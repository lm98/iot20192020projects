#ifndef __MANUALMODE
#define __MANUALMODE___

#include    "Task.h"


class ManualMode : public Task{

    public:
    void tick();
    void init(int period);
    
};

#endif 
