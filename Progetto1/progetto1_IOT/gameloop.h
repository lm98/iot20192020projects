#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

static int fade_delay;
static int level;

/*
 * Read the pot. value and translate it in a value between 1 and 8
 */
int choose_level(int);

/*
 * Pulse the led in pin specified in parameters
 */
void fade_led(int);

#endif
