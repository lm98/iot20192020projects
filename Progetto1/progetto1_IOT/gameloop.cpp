#include <Arduino.h>
#include "macros.h"
#include "gameloop.h"


int choose_level(int value){
  return value/128;
}

void fade_led(int led_pin){
  int i;
  /*
   * Turn on slowly
   */
  for(i=0;i<255;i++){
    analogWrite(led_pin,i);
    delay(fade_delay);
  }
  /*
   * Turn off slowly
   */
  for(i=255;i>0;i--){
    analogWrite(led_pin,i);
    delay(fade_delay);
  }
}
