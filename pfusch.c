// snakes_and_ladders_sim/include/board.h
#ifndef BOARD_H
#define BOARD_H

#define MAX_EDGES 6

typedef struct Edge {
    int destination;
    struct Edge *next;
} Edge;

typedef struct Node {
    int id;
    Edge *edges;
} Node;

typedef struct {
    int rows;
    int cols;
    int size;
    Node *nodes;
} Board;

Board *create_board(int rows, int cols);
void add_edge(Board *board, int from, int to);
void free_board(Board *board);

#endif


// snakes_and_ladders_sim/include/game.h
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

void play_game(Board *board, Player *player, SnakeOrLadder *snakes, int num_snakes,
               SnakeOrLadder *ladders, int num_ladders, int sides);
void simulate_games(int num_simulations, Board *board, SnakeOrLadder *snakes, int num_snakes,
                    SnakeOrLadder *ladders, int num_ladders, int sides, int max_steps);

#endif


// snakes_and_ladders_sim/include/utils.h
#ifndef UTILS_H
#define UTILS_H

int roll_die_uniform(int sides);

#endif


// snakes_and_ladders_sim/src/board.c
#include <stdlib.h>
#include "board.h"

Board *create_board(int rows, int cols) {
    Board *board = malloc(sizeof(Board));
    board->rows = rows;
    board->cols = cols;
    board->size = rows * cols;
    board->nodes = calloc(board->size, sizeof(Node));

    for (int i = 0; i < board->size; i++) {
        board->nodes[i].id = i;
        board->nodes[i].edges = NULL;
    }

    for (int i = 0; i < board->size; i++) {
        for (int j = 1; j <= MAX_EDGES && (i + j) < board->size; j++) {
            add_edge(board, i, i + j);
        }
    }

    return board;
}

void add_edge(Board *board, int from, int to) {
    Edge *edge = malloc(sizeof(Edge));
    edge->destination = to;
    edge->next = board->nodes[from].edges;
    board->nodes[from].edges = edge;
}

void free_board(Board *board) {
    for (int i = 0; i < board->size; i++) {
        Edge *edge = board->nodes[i].edges;
        while (edge) {
            Edge *temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
    free(board->nodes);
    free(board);
}


// snakes_and_ladders_sim/src/utils.c
#include <stdlib.h>
#include <time.h>
#include "utils.h"

int roll_die_uniform(int sides) {
    return (rand() % sides) + 1;
}


// snakes_and_ladders_sim/src/game.c
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "game.h"
#include "utils.h"

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

void play_game(Board *board, Player *player, SnakeOrLadder *snakes, int num_snakes,
               SnakeOrLadder *ladders, int num_ladders, int sides) {
    player->position = 0;
    player->rolls = 0;
    player->roll_sequence = malloc(player->max_steps * sizeof(int));

    while (player->position < board->size - 1 && player->rolls < player->max_steps) {
        int roll = roll_die_uniform(sides);
        int next_pos = player->position + roll;
        if (next_pos < board->size)
            player->position = next_pos;
        player->position = apply_snakes_ladders(player->position, snakes, num_snakes, ladders, num_ladders);
        player->roll_sequence[player->rolls++] = roll;
    }
}

void simulate_games(int num_simulations, Board *board, SnakeOrLadder *snakes, int num_snakes,
                    SnakeOrLadder *ladders, int num_ladders, int sides, int max_steps) {
    int total_rolls = 0;
    int min_rolls = INT_MAX;
    Player best_game;

    for (int i = 0; i < num_simulations; i++) {
        Player p;
        p.max_steps = max_steps;
        play_game(board, &p, snakes, num_snakes, ladders, num_ladders, sides);

        if (p.position == board->size - 1) {
            total_rolls += p.rolls;
            if (p.rolls < min_rolls) {
                min_rolls = p.rolls;
                best_game = p;
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
    for (int i = 0; i < min_rolls; i++) printf("%d ", best_game.roll_sequence[i]);
    printf("\n");
    free(best_game.roll_sequence);
}


// snakes_and_ladders_sim/src/main.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "game.h"

int main() {
    srand(time(NULL));

    int rows = 10, cols = 10, sides = 6;
    int max_steps = 2000, num_simulations = 10000;

    Board *board = create_board(rows, cols);

    SnakeOrLadder snakes[] = { {16, 6}, {47, 26}, {49, 11}, {56, 53}, {62, 19}, {64, 60}, {87, 24}, {93, 73}, {95, 75}, {98, 78} };
    int num_snakes = sizeof(snakes) / sizeof(snakes[0]);

    SnakeOrLadder ladders[] = { {1, 38}, {4, 14}, {9, 31}, {21, 42}, {28, 84}, {36, 44}, {51, 67}, {71, 91}, {80, 100} };
    int num_ladders = sizeof(ladders) / sizeof(ladders[0]);

    simulate_games(num_simulations, board, snakes, num_snakes, ladders, num_ladders, sides, max_steps);

    free_board(board);
    return 0;
}
