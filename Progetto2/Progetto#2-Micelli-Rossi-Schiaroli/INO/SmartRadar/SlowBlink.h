#ifndef _SLOW_BLINK_
#define _SLOW_BLINK_

#include "Task.h"
#include "Led.h"

class SlowBlink: public Task {

  int ledPin;
  Light* led;
  enum { ON, OFF } state;

  public:

    SlowBlink(int ledPin);
    void init(int period);
    void tick();
};

#endif
