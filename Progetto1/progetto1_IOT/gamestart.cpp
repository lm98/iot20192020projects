#include <Arduino.h>
#include "macros.h"
#include "gamestart.h"

int gameStart;

void blink_and_delay(int pin){ 
  digitalWrite(pin,HIGH);
  delay(DELAY_TIME);
  digitalWrite(pin,LOW);
  delay(DELAY_TIME);
}

void blink(){
  if(currentBlinkDirection==0){
    blink_and_delay(LED_VERDE_1);
    blink_and_delay(LED_VERDE_2);
    blink_and_delay(LED_VERDE_3);
    currentBlinkDirection = 1;
  } else if(currentBlinkDirection==1){
    blink_and_delay(LED_VERDE_2);
    currentBlinkDirection = 0;   
  }
}

/*
 * 
 */
 void start_game(){
  if (gameStart==0){
    Serial.println("Go!\n");
    gameStart = 1;
  }

 }
