#include <Arduino.h>
#include "macros.h"
#include "gamestart.h"

bool gameStart;

/* Blinks the argument pin one time */
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
  Serial.println("GO\n");
  gameStart=false;
  digitalWrite(LED_VERDE_1,LOW);
  digitalWrite(LED_VERDE_2,LOW);
  digitalWrite(LED_VERDE_3,LOW);
  digitalWrite(LED_BIANCO,HIGH);
  
 }