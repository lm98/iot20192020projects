#ifndef _GAMESTART_H_
#define _GAMESTART_H_

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
 * 
 */
void start_game();
 
#endif
