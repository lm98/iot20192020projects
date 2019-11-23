#ifndef _SLEEP_MODE_
 #define _SLEEP_MODE_
 
 #include"Task.h"

class SleepMode : public Task {

bool sleeping;

public:
    void init(int period);
    void tick();
    bool isSleeping();
    void setSleeping(bool sleep);
};

 #endif