#include "board.h"
#include "stats.h"
#include <stdlib.h>
#include <time.h>

int main() {
    srand((unsigned int) time(NULL));

    Board board;
    init_board(&board, 100);

    // Example configuration (1943 MB version)
    add_ladder(&board, 1, 38);
    add_ladder(&board, 4, 14);
    add_ladder(&board, 9, 31);
    add_ladder(&board, 21, 42);
    add_ladder(&board, 28, 84);
    add_ladder(&board, 36, 44);
    add_ladder(&board, 51, 67);
    add_ladder(&board, 71, 91);
    add_ladder(&board, 80, 100);

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
    run_simulations(&board, 10000, 6, 1, 1000); // 10,000 games, 6-sided die, exact win

    return 0;
}
