#include "macros.h"
#include "gamestart.h"
#include "gameloop.h"

// Global variables to be accessed
extern int game_state;
extern int score;
extern int current_led;
extern int pin_to_led[5];
extern boolean is_game_over;
extern int level;
extern float dt;

unsigned long current_time;
unsigned long previous_time=0;

void setup() {
  // Pin Setup:
  for(int y=0;y<5;y++){
    pinMode(pin_to_led[y],OUTPUT);
  }
  pinMode(POTENTIOMETER,INPUT);
  pinMode(BUTTON_START,INPUT);
  pinMode(BUTTON_DOWN,INPUT);
  
  // New Game phase setup:
  game_state = 0;
  
  //Game Loop phase setup:
  randomSeed(analogRead(A5));
  score =0;
  
  //Button management
  attachInterrupt(digitalPinToInterrupt(BUTTON_START), start_game, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_DOWN), down ,RISING);

  //Serial initialize with message
  Serial.begin(9600);
  Serial.println("Welcome to Led to Bag. Press Key TS to Start");
}

void loop() {

 // Game state management (with game_state variable)
 switch(game_state){
  case 0:
      blink();
      level=choose_level();
      dt_init(level);
      break;
  
  case 1:
      current_time=millis();
      previous_time=current_time;
      current_led=init_game();
      break;
   
  case 2:
      current_time=millis();
      if(current_time-previous_time>dt){
        game_over();
        Serial.println("Time Over");
      }
      else
      {
        all_led_off(0,4);
        switch(pin_to_led[current_led]){
          
          case WHITE_LED:
            led_in_bag();
            previous_time=millis();
            if(game_state!=3){
              current_led=init_game();
            }
            break;
  
          /*case RED_LED:digitalWrite(pin_to_led[current_led], HIGH);
            score--;
            game_over();
            break;*/
  
          default:
            digitalWrite(pin_to_led[current_led], HIGH);
            break;
       }
      } 
      break;
    
    case 3:
        score--;
        game_over();
        break;
    
  }
}
