#include "ServoMove.h"

ServoMove::ServoMove(int pin, int newPos, int delta){
  this->pin = pin;
  this->newPos = newPos;
  this->delta = delta;
}

ServoMove::init(int period){
  Task::init(period);
  servo = new ServoMotorImpl(pin);
  servo->on();
}

ServoMove::tick(){
  servo->setPosition(pos);
  pos+=delta;
}
