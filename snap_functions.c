/** @file   snap_functions.c
    @author Arabella Cryer: acr151, Haydn Boul: hbo43
    @date   16 Oct 2022
    @brief  Functions to play snap.
*/

#include <stdlib.h>
#include <stdbool.h>

// Funkit Libraries
#include "tinygl.h"
#include "navswitch.h"
#include "ir_serial.h"
#include "ir.h"
#include "button.h"

// Group 125s Modules
#include "game.h"
#include "char_matrix.h"

/**
Generates a random number 0-9 to display on the screen

Initially produces ascii value which is changed to a char
*/
char generate_random(void)
{
    char c;

    c = (rand() % 9) + 49; // Generates a random integer between 1 and 9

    // tinygl_draw_char (c, tinygl_point (0, 5));
    draw_card (c);
    srand (count);
    /* Reseed the pseudorandom number generator based on the
        number of iterations of the paced loop.  */
    return c;
}

/**
Plays the first round of snap before random numbers are shown to the screen.
This is to make the game more intuitive to play, since otherwise a blank screen would show up.
This means the same number will always appear on the funkit at first, however, never the same on both funkits.
*/
void round_one(void)
{
    if (previousState != GAMEPLAY && currentPlayer == '1') {
        c = '1';
    } else if (previousState != GAMEPLAY && currentPlayer == '2') {
        c = '4';
    } draw_card(c);
}

/**
Plays a round of snap with random numbers on LED matrix. 
Press button to snap for the same numbers on both screens.
*/
void play_round(void)
{
    if (navswitch_tick >= PACER_RATE / MESSAGE_RATE) {
        navswitch_tick = 0;

        navswitch_update ();
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            if (currentPlayer == '2' && !runOnce) {
                c = '6';
                draw_card (c);
                runOnce = true;
                /**
                The random function generates the same number for this first round.
                This 'if' prevents both funkits from producing the same number, resulting in an instant snap.
                */
            } else {
                c = generate_random();
            }
        } 
    }
}

/**
Checks for snap from either funkit each round to signify the end of the round.
*/
void check_snap(void)
{
    returnState = ir_serial_receive(&data);
    if (returnState == IR_SERIAL_OK) {
        state = CHECK_WINNER;
    }
    if (button_push_event_p(0)) {
        ir_serial_transmit (c);
        state = RECEIVE_WINNER;
    }
}