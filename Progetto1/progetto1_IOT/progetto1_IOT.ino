#include "macros.h"
#include "gamestart.h"
int livello = 0;

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
  gameStart = true;
  currentBlinkDirection = 0;
  
  Serial.begin(9600);
  Serial.println("Welcome to Led to Bag. Press Key TS to Start\n");
}

void loop() {
  // NEW GAME PHASE //
  if(gameStart){
   blink();
  }
  
  /*
   * Leggo il potenziometro e scelgo il livello
   */
  livello=scegli_livello(analogRead(POTENTIOMETER));

  
}

int scegli_livello(int valore){
  return valore/128;
}
