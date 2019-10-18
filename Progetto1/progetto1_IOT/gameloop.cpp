#include <Arduino.h>
#include "macros.h"
#include "gameloop.h"
#include "gamestart.h"

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

void down(){
  current_led++;
  if(pin_to_led[current_led]==LED_ROSSO){
      //Gestione led rosso -> gameover
      game_over(pin_to_led[current_led]);
      delay(2000);
      restart_game();
    }
}

void led_in_bag(){
  fade_led(pin_to_led[current_led]);
  //todo fare in modo che aumenti solo se non si perde
  score++;
  Serial.print("Another object in the bag! Count: ");
  Serial.print(score);
  Serial.print(" objects!\n");
}

void all_led_off(int min_led,int max_led){
  for(int i=min_led; i<=max_led;i++)
    digitalWrite(pin_to_led[i],LOW);
}

void game_over(int current_led){
  all_led_off(0,3);
  digitalWrite(LED_ROSSO, HIGH);
  Serial.print("Game Over - Score: ");
  Serial.println(score);
  //delay(2000); //Questo delay non funziona
  //Serial.println("Finito delay");
  //digitalWrite(LED_ROSSO, LOW);
  score = 0;
}
