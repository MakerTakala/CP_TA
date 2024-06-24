#include "mine.h"

int8_t dir_x[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int8_t dir_y[8] = {1, 1, 0, -1, -1, -1, 0, 1};

int8_t get_mine(int32_t board[N][M], int32_t row, int32_t col ) {
    int8_t count = 0;
    for (int k = 0; k < 8; k++) {
        int32_t x = row + dir_x[k];
        int32_t y = col + dir_y[k];
        if (x >= 0 && x < N && y >= 0 && y < M && board[x][y] == -2) {
            count++;
        }
    }
    return count;
}

void get_ans(int32_t board[N][M], int32_t ans_board[N][M]) {
    for (int i = 0; i < N; i++)  {
        for (int j = 0; j < M; j++) {
            if (board[i][j] == -2) {
                ans_board[i][j] = -2;
            }
            else {
                ans_board[i][j] = get_mine(board, i, j);
            }
        }
    }
}

void diffusion(int32_t board[N][M], int32_t ans_board[N][M], int32_t visited[N][M], int32_t row, int32_t col) {
    visited[row][col] = 1;
    board[row][col] = ans_board[row][col];
    if (board[row][col] != 0) {
        return;
    }
    for (int k = 0; k < 8; k++) {
        int32_t x = row + dir_x[k];
        int32_t y = col + dir_y[k];
        if (x >= 0 && x < N && y >= 0 && y < M && visited[x][y] == 0) {
            diffusion(board, ans_board, visited, x, y);
        }
    }
}

int32_t hit(int32_t board[N][M], int32_t row, int32_t col) {
    if (row < 0 || row >= N || col < 0 || col >= M) {
        return -1;
    }
    for (int i = 0; i < N; i++)  {
        for (int j = 0; j < M; j++) {
            if (board[i][j] < -2 || board[i][j] > 8) {
                return -1;
            }
        }
    }

    int32_t ans_board[N][M] = {{0}};
    get_ans(board, ans_board);

    for (int i = 0; i < N; i++)  {
        for (int j = 0; j < M; j++) {
            if ((board[i][j] != -2 && board[i][j] != -1) && board[i][j] != ans_board[i][j]) {
                return -1;
            }
        }
    }

    if (board[row][col] == -2) {
        return 1;
    } else if (board[row][col] == -1 && ans_board[row][col] == 1) {
       board[row][col] = ans_board[row][col];
       return 0;
    } else if(board[row][col] != -1 && board[row][col] != 0) {
        return 0;
    } 
    
    int32_t visited[N][M] = {{0}};
    diffusion(board, ans_board, visited, row, col);

    return 0;
}