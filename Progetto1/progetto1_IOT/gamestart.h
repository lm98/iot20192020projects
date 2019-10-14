#ifndef _GAMESTART_H_
#define _GAMESTART_H_

static bool gameStart;
static int currentBlinkDirection;

/* 
 * Blinks the argument pin one time 
 */
void blink_and_delay(int pin);

/*
 * Blink three leds in one way or another
 */
void blink();

#endif
