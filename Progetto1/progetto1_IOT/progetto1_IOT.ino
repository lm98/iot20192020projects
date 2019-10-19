#include "macros.h"
#include "gamestart.h"
#include "gameloop.h"

extern int gameStart;
extern int current_led;
extern int pin_to_led[5];
extern boolean gameOver;
int level;
int y;


extern void all_led_off(int,int);

float dt = DELTA_T;

unsigned long currentTime;
unsigned long previousTime=0;

void setup() {

  // Pin Setup:
  for(y=0;y<5;y++)
    pinMode(pin_to_led[y],OUTPUT);
  pinMode(POTENTIOMETER,INPUT);
  pinMode(BUTTON_START,INPUT);
  pinMode(BUTTON_DOWN,INPUT);

  // New Game phase setup:
  gameStart = 0;
  
  //Game Loop phase setup:
  randomSeed(analogRead(A5));
  score = 0;
  
  //Button management
  attachInterrupt(digitalPinToInterrupt(BUTTON_START), start_game, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_DOWN), down ,RISING);

  //Serial initialize with message
  Serial.begin(9600);
  Serial.println("Welcome to Led to Bag. Press Key TS to Start");
}

void loop() {
 
 switch(gameStart){
  
  case 0:
      blink();
      //level=choose_level();
  break;
  
  case 1:
      currentTime=millis();
      previousTime=currentTime;
      current_led=init_game();
  break;
   
  case 2:
      currentTime=millis();
      if(currentTime-previousTime>dt)
      {
        game_over();
        Serial.println("Time Over");
      }
      else
      {
        all_led_off(0,4);
        switch(pin_to_led[current_led]){
          case LED_VERDE_1:
          case LED_VERDE_2:
          case LED_VERDE_3:
            digitalWrite(pin_to_led[current_led], HIGH);
          break;
  
          case LED_BIANCO:
            previousTime=currentTime;
            led_in_bag();
            if(gameStart!=3)
              current_led=init_game();       
          break;
  
          case LED_ROSSO:
            game_over();
          break;
  
          default:
            //Do nothing  
          break;
      }
     } 
    break;
    
    case 3:
        all_led_off(0,3);
        score = 0;
        digitalWrite(LED_ROSSO, HIGH);
        Serial.print("Game Over - Score: ");
        Serial.println(score);    
        delay(2000);
        digitalWrite(LED_ROSSO, LOW);
        restart_game();
    break;
    
    default:
      //Default
    break;  
  }
}
