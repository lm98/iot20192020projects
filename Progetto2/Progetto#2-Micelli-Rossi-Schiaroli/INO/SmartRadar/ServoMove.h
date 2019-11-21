#ifndef _SERVO_MOVE_
#define _SERVO_MOVE_

#include "ServoMotorImpl.h"
#include "Task.h"

class ServoMove: public Task {
  int pin;
  bool reached;
  ServoMotor* servo;
  
  public:

    ServoMove(int pin, int delta);
    void init(int period);
    void tick();
    void setNewPosition(int newPos);
    bool getReached();
    int pos;
    int newPos;
    int delta;
};


#endif
