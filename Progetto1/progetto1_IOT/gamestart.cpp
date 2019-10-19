#include <Arduino.h>
#include "macros.h"
#include "gamestart.h"

extern int pin_to_led[5];
int gameStart;
int j; //Only for cycles

void blink_and_delay(int pin){ 
  digitalWrite(pin,HIGH);
  delay(DELAY_TIME);
  digitalWrite(pin,LOW);
  delay(DELAY_TIME);
}

void blink(){
  for(j = LED_VERDE_1; j <= LED_VERDE_3; j++){
    blink_and_delay(j);
  }
  blink_and_delay(LED_VERDE_2);
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
  for(j=LED_VERDE_1; j<=LED_ROSSO; j++)
    digitalWrite(j,LOW);
  gameStart=2;
  return init_rnd_led();
}

void restart_game(){
  if(gameStart>0){
    gameStart=0;
  }
}
