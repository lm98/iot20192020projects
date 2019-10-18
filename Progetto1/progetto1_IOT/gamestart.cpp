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
  digitalWrite(LED_ROSSO,LOW);
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

void start_game(){
 if(gameStart==0){
   Serial.println("Go!\n");
   gameStart = 1;
 }
}


int init_rnd_led(){
  return random(0, 3); 
}

int init_game(){
  int current_led=init_rnd_led();
  gameStart=2;
  return current_led;
}

void restart_game(){
  if(gameStart>0){
    gameStart=0;
  }
}
