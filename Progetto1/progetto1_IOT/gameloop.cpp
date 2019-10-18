#include <Arduino.h>
#include "macros.h"
#include "gameloop.h"
#include "gamestart.h"

extern int gameStart;
int pin_to_led[5] = {LED_VERDE_1, LED_VERDE_2, LED_VERDE_3, LED_BIANCO, LED_ROSSO};
short current_led;
int last_score = 0;

int choose_level(){
  return analogRead(POTENTIOMETER)/128;
}

float calculate_dt(float dt){
  return (dt)*(7/8);
}

void fade_led(int led_pin){
  short i;
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

void down(){
  if (gameStart==2){
    current_led++;
  if(pin_to_led[current_led]==LED_ROSSO){   // Gestione led rosso -> gameover 
      game_over(pin_to_led[current_led]);
      restart_game();
    }
  }
}

void led_in_bag(){
  fade_led(pin_to_led[current_led]);
  //todo fare in modo che aumenti solo se non si perde
  score++;
  Serial.print("Another object in the bag! Count: ");
  Serial.print(score);
  Serial.println(" objects!");
}

void all_led_off(int min_led,int max_led){
  for(short i=min_led; i<=max_led;i++)
    digitalWrite(pin_to_led[i],LOW);
}

void game_over(int current_led){
  all_led_off(0,3);
  digitalWrite(LED_ROSSO, HIGH);
  Serial.print("Game Over - Score: ");
  Serial.println(score);
  score = 0;
}

void time_over(){
  /*if(gameStart==2){
     if(score==last_score){
      game_over(current_led);
    }
    last_score = score;
  }*/
  game_over(current_led); 
}
