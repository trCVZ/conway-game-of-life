#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

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
    printf("\033[H\033[J");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", grid[y][x].symbol);
        }
        printf("\n");
    }
}

Cell updateCell(Cell cell, int y, int x, Cell tempGrid[HEIGHT][WIDTH]) {
    int countCellsAlive = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int ny = y + i;
            int nx = x + j;
            if (ny >= 0 && ny < HEIGHT && nx >= 0 && nx < WIDTH && tempGrid[ny][nx].state == ALIVE) {
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
    Cell tempGrid[HEIGHT][WIDTH];
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            tempGrid[y][x] = grid[y][x];
        }
    }
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = updateCell(grid[y][x], y, x, tempGrid);
        }
    }
}

int main() {

    initGrid(grid);
    // Create a glider
    grid[1][2].state = ALIVE;
    grid[1][2].symbol = '$';
    grid[2][3].state = ALIVE;
    grid[2][3].symbol = '$';
    grid[3][1].state = ALIVE;
    grid[3][1].symbol = '$';
    grid[3][2].state = ALIVE;
    grid[3][2].symbol = '$';
    grid[3][3].state = ALIVE;
    grid[3][3].symbol = '$';

    // Create a small exploder
    grid[10][10].state = ALIVE;
    grid[10][10].symbol = '$';
    grid[10][11].state = ALIVE;
    grid[10][11].symbol = '$';
    grid[10][12].state = ALIVE;
    grid[10][12].symbol = '$';
    grid[11][10].state = ALIVE;
    grid[11][10].symbol = '$';
    grid[11][12].state = ALIVE;
    grid[11][12].symbol = '$';
    grid[12][11].state = ALIVE;
    grid[12][11].symbol = '$';

    // Create a blinker
    grid[15][15].state = ALIVE;
    grid[15][15].symbol = '$';
    grid[15][16].state = ALIVE;
    grid[15][16].symbol = '$';
    grid[15][17].state = ALIVE;
    grid[15][17].symbol = '$';

    // Create a toad
    grid[20][20].state = ALIVE;
    grid[20][20].symbol = '$';
    grid[20][21].state = ALIVE;
    grid[20][21].symbol = '$';
    grid[20][22].state = ALIVE;
    grid[20][22].symbol = '$';
    grid[21][21].state = ALIVE;
    grid[21][21].symbol = '$';
    grid[21][22].state = ALIVE;
    grid[21][22].symbol = '$';
    grid[21][23].state = ALIVE;
    grid[21][23].symbol = '$';

    // Randomly fill the grid with alive cells
    srand(time(NULL));
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (rand() % 2 == 0) {
                grid[y][x].state = ALIVE;
                grid[y][x].symbol = '$';
            }
        }
    }

    while (1) {
        printGrid(grid);
        updateGrid(grid);

        usleep(200000);
    }

    return 0;
}