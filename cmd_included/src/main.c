#include "../include/board.h"
#include "../include/stats.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
    srand((unsigned int)time(NULL));

    // Defaults
    int board_size = 100;
    int games = 10000;
    int die_sides = 6;
    int exact_win = 1;      // 1 = must land exactly, 0 = can overshoot
    int max_turns = 1000;

    // Simple arg parsing: argv[1]=board_size, argv[2]=games, argv[3]=die_sides, argv[4]=exact_win, argv[5]=max_turns
    if (argc > 1) board_size = atoi(argv[1]);
    if (argc > 2) games = atoi(argv[2]);
    if (argc > 3) die_sides = atoi(argv[3]);
    if (argc > 4) exact_win = atoi(argv[4]);
    if (argc > 5) max_turns = atoi(argv[5]);

    Board board;
    init_board(&board, board_size);

    // Add ladders (hardcoded classic)
    add_ladder(&board, 1, 38);
    add_ladder(&board, 4, 14);
    add_ladder(&board, 9, 31);
    add_ladder(&board, 21, 42);
    add_ladder(&board, 28, 84);
    add_ladder(&board, 36, 44);
    add_ladder(&board, 51, 67);
    add_ladder(&board, 71, 91);
    add_ladder(&board, 80, 100);

    // Add snakes (hardcoded classic)
    add_snake(&board, 16, 6);
    add_snake(&board, 47, 26);
    add_snake(&board, 49, 11);
    add_snake(&board, 56, 53);
    add_snake(&board, 62, 19);
    add_snake(&board, 64, 60);
    add_snake(&board, 87, 24);
    add_snake(&board, 93, 73);
    add_snake(&board, 95, 75);
    add_snake(&board, 98, 78);

    print_board(&board);
    printf("Running %d games on %d-sized board with %d-sided die, exact_win=%d, max_turns=%d\n",
           games, board_size, die_sides, exact_win, max_turns);
    run_simulations(&board, games, die_sides, exact_win, max_turns);

    return 0;
}
