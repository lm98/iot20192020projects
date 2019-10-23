#include <Arduino.h>
#include "macros.h"
#include "gameloop.h"
#include "gamestart.h"

boolean gameOver = false;
boolean isFading = false;
extern int gameStart;

int pin_to_led[5] = { GREEN_LED_1, GREEN_LED_2, GREEN_LED_3, WHITE_LED, RED_LED};
volatile int current_led;
int last_score = 0;
int i=0; //Only for cycles

float dt;

volatile unsigned long last_interrupt_time;
volatile unsigned long interrupt_time;

int choose_level(){
  return analogRead(POTENTIOMETER)/128;
}

void dt_init(int level){
  float penalty_factor = level*100;
  dt = DELTA_T - penalty_factor;
}

void calculate_dt(){
  dt = dt * 7/8;
}

void fade_led(int led_pin){
  isFading=true;
  while(isFading && i < 255){
    analogWrite(led_pin,i);
    delay(FADE_DELAY);
    i++;
  }
    while(isFading && i > 0){
    analogWrite(led_pin,i);
    delay(FADE_DELAY);
    i--;
  }
  isFading=false;
}

void down(){
 last_interrupt_time=0;
 interrupt_time = millis();
 if ((interrupt_time - last_interrupt_time > DEBOUNCE_TIME) && gameStart == 2)
 {
    current_led++;
    if(isFading){
      gameStart=3;
      isFading=false;   
    }
 }
 last_interrupt_time = interrupt_time;
}

void led_in_bag(){ //todo fare in modo che aumenti solo se non si perde
  fade_led(pin_to_led[current_led]);
  score++;
  calculate_dt();
  Serial.print("Another object in the bag! Count: ");
  Serial.print(score);
  Serial.println(" objects!");
  Serial.println(dt);
}

void all_led_off(int min_led,int max_led){
  for(i=min_led; i<=max_led;i++)
    digitalWrite(pin_to_led[i],LOW);
}

void game_over(){
  gameStart=3;
}
