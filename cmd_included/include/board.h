#ifndef BOARD_H
#define BOARD_H

#define MAX_SIZE 100
#define MAX_SNAKES 20
#define MAX_LADDERS 20

typedef struct {
    int start;
    int end;
} Jump;

typedef struct {
    int size;
    int snakes_count;
    int ladders_count;
    Jump snakes[MAX_SNAKES];
    Jump ladders[MAX_LADDERS];
} Board;

void init_board(Board *board, int size);
void add_snake(Board *board, int start, int end);
void add_ladder(Board *board, int start, int end);
int resolve_jump(Board *board, int pos);
void print_board(Board *board);

#endif
