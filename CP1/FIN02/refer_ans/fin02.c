#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "mine.h"

int main() {

    int32_t board[16][30] = {0};
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 30; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    int row, col;
    scanf("%d %d", &row, &col);
    int state = hit(board, row, col);
    printf("%d\n", state);
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 30; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}