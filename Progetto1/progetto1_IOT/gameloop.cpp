#include <Arduino.h>
#include "macros.h"
#include "gameloop.h"
#include "gameover.h"

int pin_to_led[5] = {LED_VERDE_1,LED_VERDE_2,LED_VERDE_3, LED_BIANCO,LED_ROSSO};

int current_led;

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
    digitalWrite(pin_to_led[current_led],LOW);
}

void init_rnd_led(){
  current_led= random(0,3);
  Serial.println(current_led);
  digitalWrite(pin_to_led[current_led],HIGH);
}

void down(){
  current_led++;
}
  
