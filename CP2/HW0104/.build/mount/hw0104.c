#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "mymaze.h"

#define NORAML_TESTCASE 6
#define ERROR_TESTCASE 4
#define TOTAL_TESTCASE 10

typedef struct Testcase {
    sRoom *maze;
    uint8_t row;
    uint8_t col;
    sPath *min_path;

    char *expected_path;
    int expected_return;
    int expected_cost;
    int expected_length;
    double point;
} Testcase;

Testcase testcase[] = {
    {(sRoom[]){
        {1, 0b01110101}, {7, 0b11000011}, {2, 0b11011100}, {8, 0b11100101},
        {2, 0b00101111}, {5, 0b10111100}, {10, 0b01001010}, {2, 0b01111001},
        {9, 0b00101100}, {15, 0b01111011}, {7, 0b01111010}, {3, 0b10001101}
    }, 3, 4, NULL, "(0,0) (0,1) (0,2) (0,3) (1,3) (2,3) ", 1, 23, 6, 1.0},

    {(sRoom[]){
        {1, 0b00000000}, {7, 0b00000000}, {5, 0b00000000}, {8, 0b00000000},
        {2, 0b00000000}, {5, 0b00000000}, {9, 0b00000000}, {2, 0b00000000},
        {9, 0b00000000}, {15, 0b00000000}, {7, 0b00000000}, {3, 0b00000000}
    }, 3, 4, NULL, "(0,0) (1,0) (1,1) (1,2) (1,3) (2,3) ", 1, 22, 6, 3.0},

     {(sRoom[]){
        {1, 0b01110101}, {7, 0b11000011}, {2, 0b11011100}, {8, 0b11100101},
        {2, 0b00100011}, {5, 0b10111100}, {10, 0b01001010}, {2, 0b00111001},
        {9, 0b00101100}, {15, 0b01111011}, {7, 0b01111010}, {3, 0b10001101}
    }, 3, 4, NULL, "", 0, 0, 0, 3.0},

     {(sRoom[]){
        {10, 0b01110101}
    }, 1, 1, NULL, "(0,0) ", 1, 10, 1, 3.0},

     {(sRoom[]){
        {1, 0b01110101}, {7, 0b11000011}, {2, 0b11011100}, {8, 0b11100101},
        {2, 0b00001111}, {5, 0b10101100}, {10, 0b01011010}, {2, 0b01110001},
        {9, 0b11101100}, {15, 0b01111010}, {7, 0b01111011}, {3, 0b10001111}
    }, 3, 4, NULL, "(0,0) (0,1) (0,2) (0,3) (1,3) (1,2) (1,1) (1,0) (2,0) (2,1) (2,2) (2,3) ", 1, 71, 12, 3.0},

      {(sRoom[]){
        {1, 0b01000101}, {7, 0b11000011}, {2, 0b11011100}, {8, 0b11100101},
        {2, 0b01101111}, {5, 0b00110100}, {10, 0b01001010}, {2, 0b01111001},
        {9, 0b11111100}, {15, 0b01110011}, {100, 0b01101010}, {3, 0b10001101}
    }, 3, 4, NULL, "(0,0) (1,0) (2,0) (2,1) (1,1) (0,1) (0,2) (0,3) (1,3) (2,3) ", 1, 54, 10, 3.0},

};

double point = 0;
int8_t loglog[TOTAL_TESTCASE] = {0};


void handle_error() {
    printf("%d\n", (int)point);
    printf("Wrong testcase: ");
    for (int i = 0; i < TOTAL_TESTCASE; i++) {
        if (loglog[i] == 0) {
            printf("%d ", i + 1);
        }
    }
    exit(1);
}



int main() {
    signal(SIGSEGV, handle_error);
    signal(SIGABRT, handle_error);

    for (int i = 0; i < NORAML_TESTCASE; i++) {
        testcase[i].min_path = calloc(1, sizeof(sPath));
        int return_val = find_min_path(testcase[i].maze, testcase[i].row, testcase[i].col, testcase[i].min_path);
        sPath *min_path = testcase[i].min_path;

        bool all_pass = true;

        if (return_val == testcase[i].expected_return) {
            point += testcase[i].point / 4.0;
        } else {
            all_pass = false;
        }
        
        if (return_val == 0) {
            point += testcase[i].point * 3.0 / 4.0;
            loglog[i] = 1;
            continue;
        }
        
        if ( min_path->cost == testcase[i].expected_cost) {
            point += testcase[i].point / 4.0;
        } else {
            all_pass = false;
        }
        
        if (min_path->length == testcase[i].expected_length) {
            point += testcase[i].point / 4.0;
        } else {
            all_pass = false;
        }
        
        char *path = calloc(1, 4096);
        for (int j = 0; j < min_path->length; j++) {
            sprintf(path + strlen(path), "(%d,%d) ", min_path->pPath[j].row, min_path->pPath[j].col);
        }
        if (!strcmp(path, testcase[i].expected_path)) {
            point += testcase[i].point / 4.0;
        } else {
            all_pass = false;
        }
        
        free(testcase[i].min_path->pPath);
        free(path);

        if (all_pass) {
            loglog[i] = 1;
        }
    }
    

    signal(SIGSEGV, handle_error);
    int error_return_val;
    sPath *test_path = calloc(1, sizeof(sPath));


    error_return_val = find_min_path(testcase[0].maze, 0, 1, test_path);
    if (error_return_val == -1) point += 1;
    loglog[NORAML_TESTCASE] = 1;

    error_return_val = find_min_path(testcase[0].maze, 1, 0, test_path);
    if (error_return_val == -1) point += 1;
    loglog[NORAML_TESTCASE + 1] = 1;

    error_return_val = find_min_path(NULL, 1, 1, test_path);
    if (error_return_val == -1) point += 1;
    loglog[NORAML_TESTCASE + 2] = 1;
    
    error_return_val = find_min_path(testcase[0].maze, 1, 1, NULL);
    if (error_return_val == -1) point += 1;
    loglog[NORAML_TESTCASE + 3] = 1;

    free(test_path);
    
    printf("%d\n", (int)point);
    printf("Wrong testcase: ");
    for (int i = 0; i < NORAML_TESTCASE + ERROR_TESTCASE; i++) {
        if (loglog[i] == 0) {
            printf("%d ", i + 1);
        }
    }

    return 0;
}


