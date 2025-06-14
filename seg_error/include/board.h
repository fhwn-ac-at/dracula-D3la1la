#ifndef BOARD_H
#define BOARD_H

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
    int size;    // total squares = rows * cols
    Node *nodes;
} Board;

// Create an N x M board graph
Board *create_board(int rows, int cols);

// Add an edge from one square to another
void add_edge(Board *board, int from, int to);

// Free all allocated memory for the board
void free_board(Board *board);

#endif
