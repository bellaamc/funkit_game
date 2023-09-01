/** @file   end_game.h
    @author Arabella Cryer: acr151, Haydn Boul: hbo43
    @date   16 Oct 2022
    @brief  Functions to end a funkit game.

    This module contains all the functions required 
    to display the result of a game.
    This includes checking the result of the game after IR transmission
    and printing the result to the funkit.
*/

#ifndef END_GAME_H
#define END_GAME_H

#include "game.h"
#include "ir_serial.h"
#include "ir.h"
#include "tinygl.h"
#include "char_matrix.h"

/**
Checks the winner of a round
*/
void check_winner(char c, uint8_t data);

/**
Moves game to the final state if the winner signal has been sent.
*/
void end_game(void);

/**
Print the result of the game to the LED matrix
*/
void print_result(void);

#endif /* END_GAME_H */