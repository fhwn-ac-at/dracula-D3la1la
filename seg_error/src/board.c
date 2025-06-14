#include <stdlib.h>
#include "board.h"

Board *create_board(int rows, int cols) {
    Board *board = malloc(sizeof(Board));
    if (!board) return NULL;

    board->rows = rows;
    board->cols = cols;
    board->size = rows * cols;
    board->nodes = calloc(board->size, sizeof(Node));
    if (!board->nodes) {
        free(board);
        return NULL;
    }

    for (int i = 0; i < board->size; i++) {
        board->nodes[i].id = i;
        board->nodes[i].edges = NULL;
    }
    return board;
}

void add_edge(Board *board, int from, int to) {
    Edge *edge = malloc(sizeof(Edge));
    if (!edge) return;

    edge->destination = to;
    edge->next = board->nodes[from].edges;
    board->nodes[from].edges = edge;
}

void free_board(Board *board) {
    if (!board) return;
    for (int i = 0; i < board->size; i++) {
        Edge *edge = board->nodes[i].edges;
        while (edge) {
            Edge *tmp = edge;
            edge = edge->next;
            free(tmp);
        }
    }
    free(board->nodes);
    free(board);
}
