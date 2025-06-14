#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void run_simulations(Board *board, int games, int die_sides, int exact_win, int max_turns) {
    int total_rolls = 0, wins = 0;
    int shortest = INT_MAX;
    GameResult best_game;
    int snake_freq[MAX_SNAKES] = {0};
    int ladder_freq[MAX_LADDERS] = {0};

    for (int i = 0; i < games; i++) {
        GameResult result = play_game(board, die_sides, max_turns, exact_win, snake_freq, ladder_freq);
        if (result.win) {
            wins++;
            total_rolls += result.rolls;
            if (result.rolls < shortest) {
                shortest = result.rolls;
                best_game = result;
            }
        }
    }

    printf("\n--- Statistics ---\n");
    printf("Games run: %d\n", games);
    printf("Wins: %d\n", wins);
    if (wins) {
        printf("Average rolls to win: %.2f\n", total_rolls / (float)wins);
        printf("Shortest winning rolls: %d\nRolls: ", best_game.rolls);
        for (int i = 0; i < best_game.rolls; i++)
            printf("%d ", best_game.path[i]);
        printf("\n");
    }

    printf("\nSnake usage:\n");
    for (int i = 0; i < board->snakes_count; i++)
        printf("  %d -> %d: %d times\n", board->snakes[i].start, board->snakes[i].end, snake_freq[i]);

    printf("\nLadder usage:\n");
    for (int i = 0; i < board->ladders_count; i++)
        printf("  %d -> %d: %d times\n", board->ladders[i].start, board->ladders[i].end, ladder_freq[i]);
}
