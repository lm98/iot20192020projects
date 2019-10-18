#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

static int fade_delay = 1;
static int level;
static int score;

/*
 * Read the pot. value and translate it in a value between 1 and 8
 */
int choose_level(int);

/*
 * Pulse the led in pin specified in parameters
 */
void fade_led(int);

/**
 * Turns on a random led
 */
void init_rnd_led();

/**
 * "Moves down" the current led
 */
void down();

/**
 * Performs the bag routine
 */
void led_in_bag();

/**
 * The Game Over event, the program displays the final score and resets itself.
 */
void game_over(int);
#endif
