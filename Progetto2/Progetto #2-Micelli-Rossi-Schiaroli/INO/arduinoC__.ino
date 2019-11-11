#include "Led.h"
#include "ButtonImpl.h"

#define LED_PIN 13
#define BUTTON_PIN 2


Light* light;
Button* button;
boolean lightOn;

void setup() {
  light=new Led(LED_PIN);
  button=new ButtonImpl(BUTTON_PIN);
  lightOn=false;
}

void loop() {
  if(!lightOn && button->isPressed()){
    light->switchOn();
    lightOn=true;
  } else if(lightOn && !button->isPressed()){
    light->switchOff();
    lightOn=false;
  }
}
