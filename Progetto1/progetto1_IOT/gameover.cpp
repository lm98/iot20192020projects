#include <Arduino.h>
#include "macros.h"
#include "gameover.h"

/**
 * The Game Over event, the program displays the final score and resets itself.
 */
game_over(int score){
  Serial.println("Game Over - Score: %d\n", score);
  digitalWrite(LED_ROSSO, HIGH);
  delay(2000);
  digitalWrite(Led_ROSSO, LOW);
}
