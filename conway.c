#include <stdio.h>

#define WIDTH 50
#define HEIGHT 20

typedef enum {
    BACKGROUND = '-',
    CELL = '$'
} Grid;

void initGrid(char grid[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = '-';
        }
    }
}

void printGrid(char grid[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", grid[y][x]);
        }
        printf("\n");
    }
}

int main() {

    char grid[HEIGHT][WIDTH];
    initGrid(grid);


    grid[HEIGHT / 2][WIDTH / 2] = '$';
    printGrid(grid);






    return 0;
}