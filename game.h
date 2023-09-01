/** @file   game.h
    @author Arabella Cryer: acr151, Haydn Boul: hbo43
    @date   16 Oct 2022
    @brief  main game program
    @note   runs the game, with reference to other sub-modules
*/

#ifndef GAME_H
#define GAME_H

#define PACER_RATE 500
#define MESSAGE_RATE 20

// All the different States of the game
typedef enum {
    INTRO_SELECT,
    PLAYER_SELECT,
    PLAYER_SELECTED,
    GAMEPLAY,
    CHECK_WINNER,
    RECEIVE_WINNER,
    GAME_END
} gameState_t;

//
typedef enum {
    UNASSIGNED,
    EASY,
    MEDIUM,
    HARD
} difficulty_t;

gameState_t state;
gameState_t previousState;
difficulty_t difficulty;
uint16_t count;
uint16_t navswitch_tick;
char snap_char;
uint8_t data;
uint8_t returnState;
int playerTwoPoints;
char other_character;
char winner;



char currentPlayer;
char c;
bool runOnce;

char player_option;
char difficulty_option;



#endif // GAME_H
