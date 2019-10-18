#include "macros.h"
#include "gamestart.h"
#include "gameloop.h"
#include "TimerOne.h"

extern int gameStart;
extern int current_led;
extern int pin_to_led[5];
float dt = DELTA_T+(DELTA_T*1/8);

void setup() {
  
  // Pin Setup:
  pinMode(LED_VERDE_1,OUTPUT);
  pinMode(LED_VERDE_2,OUTPUT);
  pinMode(LED_VERDE_3,OUTPUT);
  pinMode(LED_ROSSO,OUTPUT);
  pinMode(LED_BIANCO,OUTPUT);
  pinMode(POTENTIOMETER,INPUT);
  pinMode(BUTTON_START,INPUT);
  pinMode(BUTTON_DOWN,INPUT);

  // New Game phase setup:
  gameStart = 0;

  // Timer event management
  Timer1.initialize(dt);
  //Timer1.attachInterrupt(time_over);
  //Timer1.stop();
  
  
  //Game Loop phase setup:
  randomSeed(analogRead(A5));
  fade_delay = 15;
  score = 0;
  
  //Button management
  attachInterrupt(digitalPinToInterrupt(BUTTON_START), start_game, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_DOWN), down ,RISING);

  //Serial initialize with message
  Serial.begin(9600);
  Serial.println("Welcome to Led to Bag. Press Key TS to Start");
}

void loop() {
 
  if(gameStart==0){// NEW GAME PHASE //
   blink();
   level=choose_level();
   
  }else if(gameStart==1){// GAME INIT PHASE //
    //Timer1.setPeriod(calculate_dt(dt));
    //Timer1.restart(); //Start the timeout timer
    Timer1.attachInterrupt(time_over);
    current_led=init_game();
  }else if(gameStart==2){// GAME PLAY PHASE //
    if(current_led>0 && current_led<4){
      digitalWrite(pin_to_led[current_led-1], LOW);
    }
    if(pin_to_led[current_led]==LED_BIANCO){//Gestione Led in bag
         
      led_in_bag();
      if(pin_to_led[current_led]!=LED_ROSSO){
        current_led=init_game();
      }
    }
    if(pin_to_led[current_led]!=LED_ROSSO){
      digitalWrite(pin_to_led[current_led], HIGH);
    }
  }
  
}
