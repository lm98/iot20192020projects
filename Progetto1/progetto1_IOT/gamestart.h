#ifndef _GAMESTART_H_
#define _GAMESTART_H_

/**
 * Indicates if the Leds are wether blinking in a top-down or bottom-up direction
 */
static int currentBlinkDirection;

/* 
 * Blinks the argument pin one time 
 */
void blink_and_delay(int);

/*
 * Blink three leds in one way or another
 */
void blink();

/*
 * Moves from the initial Welcome game state to the Play game state
 */
void start_game();
 
#endif
