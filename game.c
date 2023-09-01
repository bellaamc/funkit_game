/** @file   game.c
    @author Arabella Cryer: acr151, Haydn Boul: hbo43
    @date   16 Oct 2022
    @brief  main game program
    @note   runs the game, with reference to other sub-modules
*/

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "system.h"

#include "game.h"
#include "tinygl.h"
#include "../../fonts/font5x5_1.h"
#include "navswitch.h"
#include "pacer.h"
#include "button.h"
#include "ir_serial.h"
#include "ir.h"

#include "char_matrix.h"
#include "snap_functions.h"
#include "end_game.h"

tinygl_point_t point;

/**
Initialises the game settings, including player, difficulty etc,
*/
void game_init (void)
{
    currentPlayer = '0';
    difficulty = UNASSIGNED;
    state = INTRO_SELECT;
    previousState = GAME_END;
    c = 'S';
    winner = '0';
    runOnce = false;
    navswitch_tick = 0;
    count = 0;
}

/**
Initialises all the device settings
*/
void device_init (void)
{
    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    navswitch_init ();
    button_init ();
    ir_serial_init();

    pacer_init (PACER_RATE);
}

/**
Timer update for random seed generator
*/
void timer_update(void)
{
    navswitch_tick++;
    count++;
}

/**
This function selects whether a player is player 1 or 2.
*/
void choose_player (void)
{       
    display_character(player_option);
    if (navswitch_push_event_p (NAVSWITCH_WEST)) {
        if (player_option >= '2'){
            player_option = '1';
        } else {
            player_option++;
        }      
    }              
    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        if (player_option <= '1'){
            player_option = '2';
        } else {
            player_option--;
        }
    }
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        currentPlayer = player_option;
    }
}

/**
Main game loop. Includes pacer loops. Switch state changes between game states.
There is a pacer loop, which executes each function.
*/
int main (void)
{
    device_init ();
    game_init ();

    while (1)
    {
        pacer_wait ();
        tinygl_update ();
        if (state != GAMEPLAY) {
            navswitch_update ();
        }
        button_update ();

        /**
        The game works by changing states when each selection is made.
        Each state is changed by pressing the navswitch.
        */
        switch (state) {
            /**
            The intro to the game. Displays a message to select which player you are.
            */
            case INTRO_SELECT: 
                if (previousState != INTRO_SELECT) {
                    print_message("Select your player");
                }
                if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                    tinygl_clear();
                    state = PLAYER_SELECT;
                }
                previousState = INTRO_SELECT;
                break;
            
            /**
            This state allows you to select either player 1 or 2.
            Each funkit must select a different player for the game to work.
            The player selection is done by pressing the navswitch.
            */
            case PLAYER_SELECT:
                if (previousState != PLAYER_SELECT) {
                    player_option = '1';
                }
                if (currentPlayer == '0') {
                    choose_player ();
                }
                if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
                    tinygl_clear ();
                    state = PLAYER_SELECTED;
                }
                previousState = PLAYER_SELECT;
                break;
            
            /**
            Displays intro to play the game.
            This makes the game intuitive by showing a player that the game is beginning.
            */
            case PLAYER_SELECTED:
                if (previousState != PLAYER_SELECTED) {
                    print_message(" Play Snap!");
                }
                if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                    tinygl_clear();
                    state = GAMEPLAY;
                }
                previousState = PLAYER_SELECTED;
                break;

            /**
            This state allows the game to run random numbers and snap when the button is pressed.
            If the button is pressed by either funkit, the fnkits move to the next state.
            */
            case GAMEPLAY:

                round_one();
                tinygl_update();
                timer_update();
                check_snap();
                play_round();
                
                previousState = GAMEPLAY;
                break;

            /**
            If the other funkit presses the button, this funkit moves to this state. This allows the funkit to check if
            a correct snap has occurred. 
            */
            case CHECK_WINNER:
                if (previousState != CHECK_WINNER) {
                    tinygl_clear();
                }
                check_winner(c, data);
                end_game();
                previousState = CHECK_WINNER;
                break;

            /**
            If the button is pressed, the funkit moves to this stage where it finds the winner of the game.
            */
            case RECEIVE_WINNER:
                returnState = ir_serial_receive(&data);
                winner = data;
                end_game();
                break;

            /**
            Displays the result of the game.
            */
            case GAME_END: 
                print_result();
                if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
                    state = PLAYER_SELECTED;
                }
                previousState = GAME_END;
                break;
        }
    }
    return 0;
}