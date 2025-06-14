#ifndef GAME_H
#define GAME_H

#include "board.h"

typedef struct {
    int rolls;
    int win;
    int path[1000];
} GameResult;

GameResult play_game(Board *board, int die_sides, int max_turns, int exact_win, int *snake_freq, int *ladder_freq);

#endif
