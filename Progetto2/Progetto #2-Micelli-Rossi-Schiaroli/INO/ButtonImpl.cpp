#include "ButtonImpl.h"
#include "Arduino.h"

ButtonImpl::ButtonImpl(int pin){
  this->pin=pin;
  pinMode(pin,INPUT);
}

bool ButtonImpl::isPressed(){
  digitalRead(pin) == HIGH;
}
