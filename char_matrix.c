/** @file   char_matrix.c
    @author Arabella Cryer: acr151, Haydn Boul: hbo43
    @date   16 Oct 2022
    @brief  Printing to led matrix.
    @note   This prints various chars to the led matrix and converts chars.
*/

#include "tinygl.h"

/**
Displays a character on the led matrix.
This changes the character to a string so it can be displayed by tinygl.
@param character takes the character that you wish to print to the matrix.
*/
void display_character (char character)
{
    tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

/**
Prints a string on the led matrix.
@param string is the words you wish to print to the matrix.
*/
void print_message(char* string)
{
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(string);
}

/**
Displays a card on the led matrix.
@param character takes the character that you wish to print to the matrix.
*/
void draw_card(char character)
{
    tinygl_draw_char(character, tinygl_point (0, 5));
}
