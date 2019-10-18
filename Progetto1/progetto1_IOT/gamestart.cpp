#include <Arduino.h>
#include "macros.h"
#include "gamestart.h"

extern int pin_to_led[5];
short gameStart;

void blink_and_delay(int pin){ 
  digitalWrite(pin,HIGH);
  delay(DELAY_TIME);
  digitalWrite(pin,LOW);
  delay(DELAY_TIME);
}

void blink(){
  /*
   * Accendo i tre led verdi in sequenza
   */
//  digitalWrite(LED_ROSSO,LOW);
//  if(currentBlinkDirection==0){
//    blink_and_delay(LED_VERDE_1);
//    blink_and_delay(LED_VERDE_2);
//    blink_and_delay(LED_VERDE_3);
//    currentBlinkDirection = 1;
//  } else if(currentBlinkDirection==1){
//    blink_and_delay(LED_VERDE_2);
//    currentBlinkDirection = 0;   
//  }
  digitalWrite(LED_ROSSO,LOW);
  for(int i = LED_VERDE_1; i <= LED_VERDE_3; i++){
    blink_and_delay(i);
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
  int current_led;
  for(int i=0; i<=4;i++)
    digitalWrite(pin_to_led[i],LOW);
  current_led=init_rnd_led();
  gameStart=2;
  return current_led;
}

void restart_game(){
  if(gameStart>0){
    gameStart=0;
  }
}
