#include <Arduino.h>
#include "macros.h"
#include "gameloop.h"
#include "gamestart.h"

boolean is_game_over = false;
volatile boolean is_fading = true;
extern int game_state;

int pin_to_led[5] = { GREEN_LED_1, GREEN_LED_2, GREEN_LED_3, WHITE_LED, RED_LED};
volatile int current_led;
int last_score = 0;

float dt;
unsigned long last_debounce_time = 0;

int choose_level(){
  return analogRead(POTENTIOMETER)/128;
}

void dt_init(int level){
  float penalty_factor = level*PENALTY;
  dt = DELTA_T - penalty_factor;
}

void calculate_dt(){
  dt = dt * 7/8;
}

void fade_led(int led_pin){
  is_fading=true;
  int i;
  for(i=0; (is_fading==true && i<255) ;i++){
    analogWrite(led_pin,i);
    delay(FADE_DELAY);
  }
  for(i=255; (is_fading==true && i>=0) ;i--){
    analogWrite(led_pin,i);
    delay(FADE_DELAY);
  }
  is_fading=false;
}

void down(){
 unsigned long current_time = millis();
 if ((current_time - last_debounce_time > DEBOUNCE_TIME) && game_state == 2){
    last_debounce_time = current_time;
    current_led++;
    if(current_led==4){
      game_state=3;
      is_fading=false;
    }
 }
}

void led_in_bag(){
  fade_led(pin_to_led[current_led]);
  score++;
  calculate_dt();
  Serial.print("Another object in the bag! Count: ");
  Serial.print(score);
  Serial.println(" objects!");
  Serial.println(dt);
}

void all_led_off(int min_led,int max_led){
  for(int i=min_led; i<=max_led;i++)
    digitalWrite(pin_to_led[i],LOW);
}

void game_over(){
  game_state=3;
}
