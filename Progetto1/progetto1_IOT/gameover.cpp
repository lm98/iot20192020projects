#include <Arduino.h>
#include "macros.h"
#include "gameover.h"

/**
 * The Game Over event, the program displays the final score and resets itself.
 */
void game_over(int score){
  Serial.println("Game Over - Score: score");
  digitalWrite(LED_ROSSO, HIGH);
  delay(2000);
  digitalWrite(LED_ROSSO, LOW);
}
