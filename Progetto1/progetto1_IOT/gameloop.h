#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

/*
 * Read the pot. value and translate it in a value between 1 and 8
 */
int choose_level();

/*
 * Pulse the led in pin specified in parameters
 */
void fade_led(int);

/*
 * Turns on a random led
 */
void init_rnd_led();

/*
 * "Moves down" the current led
 */
void down();

/*
 * Performs the bag routine
 */
void led_in_bag();

/*
 * The Game Over event, the program displays the final score and resets itself.
 */
void game_over();

/*
 * Time over event
 */
void time_over();

/*
 * Calculate 1/8 of the time
 */
float calculate_dt(float);

/*
 * Initialize the delta time from the level
 */
void dt_init(int);

/*
 * Turns off every led in pin range
 */
void all_led_off(int,int);
#endif
