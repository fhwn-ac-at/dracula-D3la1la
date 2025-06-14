#include "game.h"
#include <stdlib.h>

int roll_die(int sides) {
    return (rand() % sides) + 1;
}

GameResult play_game(Board *board, int die_sides, int max_turns, int exact_win, int *snake_freq, int *ladder_freq) {
    GameResult result = {0};
    int pos = 0;

    for (int turn = 0; turn < max_turns; ++turn) {
        int roll = roll_die(die_sides);
        if (pos + roll <= board->size || !exact_win)
            pos += roll;

        int old_pos = pos;
        pos = resolve_jump(board, pos);

        // Stats
        if (old_pos != pos) {
            for (int i = 0; i < board->snakes_count; i++) {
                if (board->snakes[i].start == old_pos && board->snakes[i].end == pos)
                    snake_freq[i]++;
            }
            for (int i = 0; i < board->ladders_count; i++) {
                if (board->ladders[i].start == old_pos && board->ladders[i].end == pos)
                    ladder_freq[i]++;
            }
        }

        result.path[result.rolls++] = roll;
        if (pos == board->size) {
            result.win = 1;
            break;
        }
    }

    return result;
}
