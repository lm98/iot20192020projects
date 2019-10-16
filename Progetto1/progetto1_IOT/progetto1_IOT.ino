#include "macros.h"
#include "gamestart.h"
#include "gameloop.h"
#include "gameover.h"

extern int gameStart;

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

  //Button management
  attachInterrupt(digitalPinToInterrupt(BUTTON_START), start_game, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_DOWN), down ,RISING);
  Serial.begin(9600);
  Serial.println("Welcome to Led to Bag. Press Key TS to Start\n");
}

void loop() {
  
  // NEW GAME PHASE //
  if(gameStart==0){
   blink();
  }else if(gameStart==1){
    init_rnd_led();
    gameStart++;
  }else{
    
  }
  
  level = choose_level(analogRead(POTENTIOMETER));
}
