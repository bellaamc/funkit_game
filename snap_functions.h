/** @file   snap_functions.c
    @author Arabella Cryer: acr151, Haydn Boul: hbo43
    @date   16 Oct 2022
    @brief  Functions to play snap.

    This module provides all the functions to play rounds of snap.
    This includes a random number generator, the function for the first round
    and functions to check if a person has snapped.
*/

#ifndef SNAP_FUNCTIONS_H
#define SNAP_FUNCTIONS_H

#include <stdlib.h>
#include "tinygl.h"
#include "navswitch.h"
#include "ir_serial.h"
#include "ir.h"
#include "button.h"

/**
Generates a random number 0-9 to display on the screen

Initially produces ascii value which is changed to a char
*/
char generate_random(void);

/**
Plays the first round of snap before random numbers are shown to the screen.
This is to make the game more intuitive to play, since otherwise a blank screen would show up.
This means the same number will always appear on the funkit at first, however, never the same on both funkits.
*/
void round_one(void);

/**
Plays a round of snap with random numbers on LED matrix. 
Press button to snap for the same numbers on both screens.
*/
void play_round(void);

/**
Checks for snap from either funkit each round to signify the end of the round.
*/
void check_snap(void);

#endif /* SNAP_FUNCTIONS_H  */