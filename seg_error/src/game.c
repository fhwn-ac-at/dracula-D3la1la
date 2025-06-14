#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "game.h"
#include "utils.h"

// Move the player if on snake or ladder start position
static int apply_snakes_ladders(int pos, SnakeOrLadder *snakes, int num_snakes,
                                SnakeOrLadder *ladders, int num_ladders) {
    for (int i = 0; i < num_snakes; i++) {
        if (snakes[i].start == pos) return snakes[i].end;
    }
    for (int i = 0; i < num_ladders; i++) {
        if (ladders[i].start == pos) return ladders[i].end;
    }
    return pos;
}

void play_game(Board *board, Player *player,
               SnakeOrLadder *snakes, int num_snakes,
               SnakeOrLadder *ladders, int num_ladders,
               int sides) {
    player->position = 0;
    player->rolls = 0;
    player->roll_sequence = malloc(player->max_steps * sizeof(int));
    if (!player->roll_sequence) return;

    while (player->position < board->size - 1 && player->rolls < player->max_steps) {
        int roll = roll_die_uniform(sides);
        int next_pos = player->position + roll;

        // Check exact or overshoot rule (assumes no move if overshoot)
        if (next_pos < board->size)
            player->position = next_pos;

        player->position = apply_snakes_ladders(player->position, snakes, num_snakes, ladders, num_ladders);

        player->roll_sequence[player->rolls++] = roll;
    }
}

void simulate_games(int num_simulations, Board *board,
                    SnakeOrLadder *snakes, int num_snakes,
                    SnakeOrLadder *ladders, int num_ladders,
                    int sides, int max_steps) {

    int total_rolls = 0;
    int min_rolls = INT_MAX;
    Player best_game = {0};

    for (int i = 0; i < num_simulations; i++) {
        Player p = {0};
        p.max_steps = max_steps;
        play_game(board, &p, snakes, num_snakes, ladders, num_ladders, sides);

        if (p.position == board->size - 1) {
            total_rolls += p.rolls;
            if (p.rolls < min_rolls) {
                if (best_game.roll_sequence) free(best_game.roll_sequence);
                best_game = p; // Save the best game
            } else {
                free(p.roll_sequence);
            }
        } else {
            free(p.roll_sequence);
        }
    }

    printf("\nSimulation Results:\n--------------------\n");
    printf("Games Simulated: %d\n", num_simulations);
    printf("Average Rolls to Win: %.2f\n", (float)total_rolls / num_simulations);
    printf("Shortest Game: %d rolls\n", min_rolls);
    printf("Shortest Roll Sequence: ");
    for (int i = 0; i < min_rolls; i++) {
        printf("%d ", best_game.roll_sequence[i]);
    }
    printf("\n");

    if (best_game.roll_sequence)
        free(best_game.roll_sequence);
}
