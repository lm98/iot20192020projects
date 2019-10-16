#include <Arduino.h>
#include "macros.h"
#include "gameloop.h"

int pin_to_led[5] = {LED_VERDE_1,LED_VERDE_2,LED_VERDE_3, LED_BIANCO,LED_ROSSO};
int led;
//int current_i=0;
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

void init_rnd_led(){
  led= random(0,3);
  Serial.println(led);
  digitalWrite(pin_to_led[led],HIGH);
}

void down(){
  digitalWrite(pin_to_led[led],LOW);
  
  led++;
  digitalWrite(pin_to_led[led],HIGH);
}
