#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "game.h"

int main(void) {
    srand(time(NULL));

    int rows = 10;
    int cols = 10;
    int sides = 6;
    int max_steps = 2000;
    int num_simulations = 10000;

    Board *board = create_board(rows, cols);
    if (!board) {
        fprintf(stderr, "Failed to create board\n");
        return 1;
    }

    // Snakes: start -> end
    SnakeOrLadder snakes[] = {
        {16, 6}, {47, 26}, {49, 11}, {56, 53},
        {62, 19}, {64, 60}, {87, 24}, {93, 73},
        {95, 75}, {98, 78}
    };
    int num_snakes = sizeof(snakes) / sizeof(snakes[0]);

    // Ladders: start -> end
    SnakeOrLadder ladders[] = {
        {1, 38}, {4, 14}, {9, 31}, {21, 42},
        {28, 84}, {36, 44}, {51, 67}, {71, 91},
        {80, 100}
    };
    int num_ladders = sizeof(ladders) / sizeof(ladders[0]);

    simulate_games(num_simulations, board, snakes, num_snakes, ladders, num_ladders, sides, max_steps);

    free_board(board);

    return 0;
}
