#include "ServoMove.h"

ServoMove::ServoMove(int pin, int newPos, int delta){
  this->pin = pin;
  this->newPos = newPos;
  this->delta = delta;
}

void ServoMove::init(int period){
  Task::init(period);
  servo = new ServoMotorImpl(pin);
  servo->on();
}

void ServoMove::tick(){
  servo->setPosition(pos);
  pos+=delta;
}
