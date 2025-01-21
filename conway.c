#include <stdio.h>
#include <stdbool.h>

#define WIDTH 50
#define HEIGHT 20

Cell grid[HEIGHT][WIDTH];

typedef enum {
    DEAD,
    ALIVE
} CellState;

typedef struct {
    char symbol;
    CellState state;
} Cell;

void initGrid(Cell grid[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x].symbol = '-';
            grid[y][x].state = DEAD;
        }
    }
}

void printGrid(Cell grid[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", grid[y][x].symbol);
        }
        printf("\n");
    }
}

Cell updateCell(Cell cell, int y, int x) {
    int ymax = y + 3;
    int xmax = x + 3;
    int countCellsAlive = 0;
    for (y - 1; y < ymax; y++) {
        for (x - 1; x < xmax; x++) {
            if (grid[y][x].state == ALIVE) {
                countCellsAlive++;
            }
        }
    }
    if (cell.state == ALIVE && countCellsAlive >= 2 && countCellsAlive > 3) {
        cell.state = DEAD;
        cell.symbol = '-';
        return cell;
    }
    else if (cell.state == DEAD && countCellsAlive == 3) {
        cell.state = ALIVE;
        cell.symbol = '$';
        return cell;
    }
    return cell;
}


void updateGrid(Cell grid[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = updateCell(grid[y][x], x, y);
        }
    }
}


int main() {

    initGrid(grid);

    Cell test;
    test.state = DEAD;

    grid[HEIGHT / 2][WIDTH / 2].symbol = '$';
    printGrid(grid);

    return 0;
}