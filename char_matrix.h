/** @file   char_matrix.h
    @author Arabella Cryer: acr151, Haydn Boul: hbo43
    @date   16 Oct 2022
    @brief  Printing to led matrix.

    This prints various chars to the led matrix and converts chars.
    This module provides a simple way to print various things to the led matrix.
*/

#ifndef CHAR_MATRIX_H
#define CHAR_MATRIX_H

#include "tinygl.h"

/**
Displays a character on the led matrix.
@param character takes the character that you wish to print to the matrix.
*/
void display_character (char character);

/**
Prints a string on the led matrix.
@param string is the words you wish to print to the matrix.
*/
void print_message(char* string);

/**
Displays a card on the led matrix.
@param character takes the character that you wish to print to the matrix.
*/
void draw_card(char character);

#endif // CHAR_MATRIX_H 