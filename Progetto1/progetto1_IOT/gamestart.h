#ifndef _GAMESTART_H_
#define _GAMESTART_H_

/* 
 * Blinks the argument pin one time , manages all the scearios
 */
void blink_and_delay(int, int);

/*
 * Moves from the initial Welcome game state to the Play game state
 */
void start_game();

/**
 * Inits the game, randomly chooses a led to turn on and start the timer
 */
int init_game();

/**
 * Restarts the game to it's initial state
 */
void restart_game();
#endif
