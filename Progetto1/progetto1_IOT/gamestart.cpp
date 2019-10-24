#include <Arduino.h>
#include "macros.h"
#include "gamestart.h"

extern int pin_to_led[5];
extern int score;
int game_state;
int level;
volatile int pin = GREEN_LED_1;
volatile bool up = false;

void blink_and_delay(int first_pin,int last_pin){ 
  digitalWrite(pin,HIGH);
  delay(DELAY_TIME);
  digitalWrite(pin,LOW);
  delay(DELAY_TIME);
  if (pin == last_pin){
    up = true;
  } else if(pin == first_pin){
    up = false;
  }
  up ? pin--: pin++;
}

void start_game(){
 if(game_state==0){
   Serial.println("Go!\n");
   game_state = 1;
 }
}

int init_rnd_led(){
  return random(0, 3); 
}

int init_game(){
  for(int j=GREEN_LED_1; j<=RED_LED; j++)
    digitalWrite(j,LOW);
  game_state=2;
  return init_rnd_led();
}

void restart_game(){
  if(game_state>0){
    game_state=0;
    score = 0;
  }
}
