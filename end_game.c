/** @file   end_game.c
    @author Arabella Cryer: acr151, Haydn Boul: hbo43
    @date   16 Oct 2022
    @brief  Functions to end a funkit game.
*/

#include <stdbool.h>
#include <stdint.h>
#include "game.h"
#include "ir_serial.h"
#include "ir.h"
#include "tinygl.h"
#include "char_matrix.h"

/**
Checks the winner of a round
*/
void check_winner(char c, uint8_t data)
{
    if (currentPlayer == '1') {
        if (data == c) {
            winner = '2';
        } else {
            winner = '1';
        }
    } else {
        if (data == c) {
            winner = '1';
        } else {
            winner = '2';
        }
    }
    
    ir_serial_transmit (winner);
}

/**
Moves game to the final state if the winner signal has been sent.
*/
void end_game(void)
{
    if (winner != '0') {
        state = GAME_END;
    }
}

/**
Print the result of the game to the LED matrix
*/
void print_result(void)
{
    if (previousState != GAME_END) {        
        if (currentPlayer == winner) {
            print_message(" You won!");
        } else {
            print_message(" You lost!");
        }
    }
}