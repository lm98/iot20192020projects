#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include "ServoMotor.h"
#include <Arduino.h>
#include "ServoTimer2.h"

class ServoMotorImpl: public ServoMotor {


public:
  ServoMotorImpl(int pin);

  void on();
  void setPosition(int angle);
  void off();
  void setSpeed(int speed);
  int getSpeed();

private:
  int pin; 
  ServoTimer2 motor; 
  int speed = 0;
  int delayTime = 500;
};

#endif
