#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "conway.h"

void initGrid(Cell** grid, int height, int width) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[y][x].symbol = '-';
            grid[y][x].state = DEAD;
        }
    }
}

void printGrid(Cell** grid, int height, int width) {
    printf("\033[H\033[J");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%c", grid[y][x].symbol);
        }
        printf("\n");
    }
}

Cell updateCell(Cell cell, int y, int x, Cell** tempGrid, int height, int width) {
    int countCellsAlive = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int ny = y + i;
            int nx = x + j;
            if (ny >= 0 && ny < height && nx >= 0 && nx < width && tempGrid[ny][nx].state == ALIVE) {
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


void updateGrid(Cell** grid, int height, int width) {
    Cell** tempGrid = malloc(height * sizeof(Cell*));
    for (int i = 0; i < height; i++) {
        tempGrid[i] = malloc(width * sizeof(Cell));
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            tempGrid[y][x] = grid[y][x];
        }
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[y][x] = updateCell(grid[y][x], y, x, tempGrid, height, width);
        }
    }
    for (int i = 0; i < height; i++) {
        free(tempGrid[i]);
    }
    free(tempGrid);
}

int main() {
    char input[10];
    int width;
    int height;

    printf("Default WIDTH : %d\n", DEFAULT_WIDTH);
    printf("Chose the width of the grid (between 5 and 75) : ");

    if (fgets(input, sizeof(input), stdin) != NULL) {
        width = atoi(input);
        if (width >= 5 && width <= 75) {
            printf("Width is set to %d.\n", width);
        }
        else {
            width = 50;
            printf("Width is set to default value : %d.\n", width);
        }
    }

    printf("Default HEIGHT : %d\n", DEFAULT_HEIGHT);
    printf("Chose the height of the grid (between 5 and 55) : ");

    if (fgets(input, sizeof(input), stdin) != NULL) {
        height = atoi(input);
        if (height >= 5 && height <= 55) {
            printf("height is set to %d.\n", height);
        }
        else {
            height = 50;
            printf("height is set to default value : %d.\n", height);
        }
    }

    Cell** grid = malloc(height * sizeof(Cell*));
    for (int i = 0; i < height; i++) {
        grid[i] = malloc(width * sizeof(Cell));
    }
    initGrid(grid, height, width);

    srand(time(NULL));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (rand() % 2 == 0) {
                grid[y][x].state = ALIVE;
                grid[y][x].symbol = '$';
            }
        }
    }

    while (1) {
        printGrid(grid, height, width);
        updateGrid(grid, height, width);
        usleep(200000);
    }

    for (int i = 0; i < height; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}
