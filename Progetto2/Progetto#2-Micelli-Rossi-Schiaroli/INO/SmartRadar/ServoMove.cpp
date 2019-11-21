#include "ServoMove.h"
#include <Arduino.h>

ServoMove::ServoMove(int pin, int delta){
  this->pin = pin;
  this->delta = delta;
}

void ServoMove::init(int period){
  Task::init(period);
  servo = new ServoMotorImpl(pin);
  servo->on();
  pos = 0;
  newPos = 0;
}

void ServoMove::tick(){ 

  if(pos == newPos){
    this -> setActive(false);
  }
  else
  {
    if(pos>newPos){
      pos-=delta;
      servo->setPosition(pos);
    }
    else if(pos<newPos){
      pos+=delta;
      servo->setPosition(pos);
    }
  }
}

void ServoMove::setNewPosition(int newPos){
  this->newPos = newPos;
}

void ServoMove::restart(){
  pos = 0;
  newPos = 0;
  servo->setPosition(pos);
}

int ServoMove::getPos(){
  return pos;
}

int ServoMove::getNewPos(){
  return newPos;
}

int ServoMove::getDelta(){
  return delta;
}