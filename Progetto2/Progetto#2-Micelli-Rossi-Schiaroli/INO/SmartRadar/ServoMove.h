#ifndef _SERVO_MOVE_
#define _SERVO_MOVE_

#include "ServoMotorImpl.h"
#include "Task.h"

class ServoMove: public Task {
  int pin;
  int pos = 0;
  int newPos;
  int delta;
  ServoMotor* servo;
  
  public:

    ServoMove(int pin, int newPos, int delta);
    void init(int period);
    void tick();
};


#endif
