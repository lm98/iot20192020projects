#include "macros.h"
#include "gamestart.h"
#include "gameloop.h"

// Global variables to be accessed
extern int game_state;
extern int current_led;
extern int pin_to_led[5];
extern boolean is_game_over;
extern int level;
extern float dt;
extern int score;

unsigned long current_time;
unsigned long previous_time=0;

void setup() {
  // Pin Setup:
  for(int led=0;led<N_LEDS;led++){
    pinMode(pin_to_led[led],OUTPUT);
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
      blink_and_delay(GREEN_LED_1, GREEN_LED_3);
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
      } else {
          all_led_off(0,4);
          switch(pin_to_led[current_led]){
          
            case WHITE_LED:
              led_in_bag();
              previous_time=millis();
              if(game_state!=3){
                 current_led=init_game();
              }
              break;

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
