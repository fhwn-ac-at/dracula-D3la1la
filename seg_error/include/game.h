#ifndef GAME_H
#define GAME_H

#include "board.h"

typedef struct {
    int start;
    int end;
} SnakeOrLadder;

typedef struct {
    int position;
    int rolls;
    int max_steps;
    int *roll_sequence;
} Player;

void play_game(Board *board, Player *player,
               SnakeOrLadder *snakes, int num_snakes,
               SnakeOrLadder *ladders, int num_ladders,
               int sides);

void simulate_games(int num_simulations, Board *board,
                    SnakeOrLadder *snakes, int num_snakes,
                    SnakeOrLadder *ladders, int num_ladders,
                    int sides, int max_steps);

#endif
