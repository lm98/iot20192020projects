#include "macros.h"
#include "gamestart.h"
#include "gameloop.h"

extern int gameStart;
extern int current_led;
extern int pin_to_led[5];

void setup() {
  // pin setup:
  pinMode(LED_VERDE_1,OUTPUT);
  pinMode(LED_VERDE_2,OUTPUT);
  pinMode(LED_VERDE_3,OUTPUT);
  pinMode(LED_ROSSO,OUTPUT);
  pinMode(LED_BIANCO,OUTPUT);
  pinMode(POTENTIOMETER,INPUT);
  pinMode(BUTTON_START,INPUT);
  pinMode(BUTTON_DOWN,INPUT);

  // New Game phase setup:
  currentBlinkDirection = 0;
  gameStart = 0;
  
  
  //Game Loop phase setup:
  randomSeed(analogRead(A5));
  level = 0;
  fade_delay = 10;
  score = 0;
  
  //Button management
  attachInterrupt(digitalPinToInterrupt(BUTTON_START), start_game, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_DOWN), down ,RISING);
  Serial.begin(9600);
  Serial.println("Welcome to Led to Bag. Press Key TS to Start");
}

void loop() {
 
  if(gameStart==0){// NEW GAME PHASE //
   blink();
   
  }else if(gameStart==1){// GAME INIT PHASE //
    current_led=init_game();
    
  }else if(gameStart==2){// GAME PLAY PHASE //
    if(current_led>0 && current_led<4){
      digitalWrite(pin_to_led[current_led-1], LOW);
    }
    if(pin_to_led[current_led]==LED_BIANCO){
      //gestione bag
      led_in_bag();
      if(pin_to_led[current_led]!=LED_ROSSO){
        current_led=init_game();
      }
    }
    if(pin_to_led[current_led]==LED_ROSSO){
      //gestione led rosso -> gameover
      //game_over(pin_to_led[current_led]);
      //restart_game();
    }else{
      digitalWrite(pin_to_led[current_led], HIGH);
    }
  }
  
  //level = choose_level(analogRead(POTENTIOMETER));
}
