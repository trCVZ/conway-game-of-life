#ifndef CONWAY_H
#define CONWAY_H

#define DEFAULT_WIDTH 50
#define DEFAULT_HEIGHT 50

typedef enum {
    DEAD,
    ALIVE
} CellState;

typedef struct {
    char symbol;
    CellState state;
} Cell;

void initGrid(Cell** grid, int height, int width);
void printGrid(Cell** grid, int height, int width);
Cell updateCell(Cell cell, int y, int x, Cell** tempGrid, int height, int width);
void updateGrid(Cell** grid, int height, int width);

#endif