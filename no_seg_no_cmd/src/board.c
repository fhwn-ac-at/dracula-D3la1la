#include "board.h"
#include <stdio.h>

void init_board(Board *board, int size) {
    board->size = size;
    board->snakes_count = 0;
    board->ladders_count = 0;
}

void add_snake(Board *board, int start, int end) {
    if (board->snakes_count < MAX_SNAKES)
        board->snakes[board->snakes_count++] = (Jump){start, end};
}

void add_ladder(Board *board, int start, int end) {
    if (board->ladders_count < MAX_LADDERS)
        board->ladders[board->ladders_count++] = (Jump){start, end};
}

int resolve_jump(Board *board, int pos) {
    for (int i = 0; i < board->snakes_count; i++)
        if (board->snakes[i].start == pos)
            return board->snakes[i].end;
    for (int i = 0; i < board->ladders_count; i++)
        if (board->ladders[i].start == pos)
            return board->ladders[i].end;
    return pos;
}

void print_board(Board *board) {
    printf("Snakes:\n");
    for (int i = 0; i < board->snakes_count; i++)
        printf("  %d -> %d\n", board->snakes[i].start, board->snakes[i].end);
    printf("Ladders:\n");
    for (int i = 0; i < board->ladders_count; i++)
        printf("  %d -> %d\n", board->ladders[i].start, board->ladders[i].end);
}
