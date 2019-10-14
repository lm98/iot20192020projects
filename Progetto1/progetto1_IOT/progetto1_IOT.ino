#include "macros.h"
int livello = 0;

bool gameStart;
int currentBlinkDirection;

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
   Serial.println("C");
  }
  
  /*
   * Leggo il potenziometro e scelgo il livello
   */
  livello=scegli_livello(analogRead(POTENTIOMETER));

  
}

void blink(){
  if(currentBlinkDirection==0){
    blink_and_delay(LED_VERDE_1);
    blink_and_delay(LED_VERDE_2);
    blink_and_delay(LED_VERDE_3);
    currentBlinkDirection = 1;
  } else if(currentBlinkDirection==1){
    blink_and_delay(LED_VERDE_2);
    currentBlinkDirection = 0;   
  }
}

void blink_and_delay(int pin){ 
  digitalWrite(pin,HIGH);
  delay(DELAY_TIME);
  digitalWrite(pin,LOW);
  delay(DELAY_TIME);
}

int scegli_livello(int valore){
  return valore/128;
}
