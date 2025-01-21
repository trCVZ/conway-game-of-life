#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define WIDTH 50
#define HEIGHT 20

typedef enum {
    DEAD,
    ALIVE
} CellState;

typedef struct {
    char symbol;
    CellState state;
} Cell;

Cell grid[HEIGHT][WIDTH];

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
    int countCellsAlive = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int ny = y + i;
            int nx = x + j;
            if (ny >= 0 && ny < HEIGHT && nx >= 0 && nx < WIDTH && grid[ny][nx].state == ALIVE) {
                countCellsAlive++;
            }
        }
    }
    if (cell.state == ALIVE && (countCellsAlive < 2 || countCellsAlive > 3)) {
        cell.state = DEAD;
        cell.symbol = '-';
    }
    else if (cell.state == DEAD && countCellsAlive == 3) {
        cell.state = ALIVE;
        cell.symbol = '$';
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

    grid[1][2].state = ALIVE; grid[1][2].symbol = '$';
    grid[2][3].state = ALIVE; grid[2][3].symbol = '$';
    grid[3][1].state = ALIVE; grid[3][1].symbol = '$';
    grid[3][2].state = ALIVE; grid[3][2].symbol = '$';
    grid[3][3].state = ALIVE; grid[3][3].symbol = '$';

    grid[10][10].state = ALIVE; grid[10][10].symbol = '$';
    grid[10][11].state = ALIVE; grid[10][11].symbol = '$';
    grid[11][10].state = ALIVE; grid[11][10].symbol = '$';
    grid[11][11].state = ALIVE; grid[11][11].symbol = '$';

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (rand() % 5 == 0) {
                grid[i][j].state = ALIVE;
                grid[i][j].symbol = '$';
            }
        }
    }


    while (1) {
        printf("==================================================");
        printGrid(grid);
        updateGrid(grid);

        sleep(1);
    }

    return 0;
}