#ifndef _SERVO_MOVE_
#define _SERVO_MOVE_

#include "ServoMotorImpl.h"
#include "Task.h"

class ServoMove: public Task {
  int pin;
  int pos;
  int newPos;
  int delta;
  ServoMotor* servo;
  
  public:

    ServoMove(int pin, int delta);
    void init(int period);
    void tick();
    void setNewPosition(int newPos);
    void restart();
    int getPos();
    int getNewPos();
    int getDelta();
};


#endif
