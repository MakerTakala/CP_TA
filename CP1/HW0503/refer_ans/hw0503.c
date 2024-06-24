#include "mysphere.h"
#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define CASE 10

double testcase[CASE][5] = {
    {10, 1, 0, 0, 1},
    {10, 0, 1, 0, 2},
    {10, 0, 0, 1, 3},
    {10, 1, 1, 0, 4},
    {10, 0, 1, 1, 5},
    {10, 1, 0, 1, 6},
    {0, 1, 1, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 1, 0, 0, 3}
};

double ans[CASE] = {311.02, 301.59, 285.88, 289.03, 274.89, 257.61, -1, -1, -1};
int32_t return_state[CASE] = {1, 1, 1, 1, 1, 1, -1, -1, 0};
int wrong[10] = {0}; 
int total_score = 0;


void signal_handler(int signum) {
    wrong[9] = 1;
    printf("%d\n", total_score);
    printf("Wrong cases:");
    for (int i = 0; i < CASE; i++) {
        if (wrong[i]) {
            printf("%d ", i + 1);
        }
    }
    exit(0);
}

int main() {
    
    
    for (int i = 0; i < CASE - 1; i++) {
        double area = 0;
        int32_t state = get_cap_area(testcase[i][0], testcase[i][1], testcase[i][2], testcase[i][3], testcase[i][4], &area);
        if (ans[i] == -1) {
            if (state == return_state[i]) {
                total_score += 2;
            }
            else {
                wrong[i] = 1;
            }
        }
        else {
            if (state == return_state[i] && fabs(area - ans[i]) < 0.01) {
                total_score += 2;
            }
            else {
                wrong[i] = 1;
            }
        }
    }


    signal(SIGSEGV, signal_handler);


    int32_t state = get_cap_area(3, 1, 1, 1, 0, NULL);
    if (state == -1) {
        total_score += 2;
    } 
    else {
        wrong[9] = 1;
    }

    printf("%d\n", total_score);
    printf("Wrong cases:");
    for (int i = 0; i < CASE; i++) {
        if (wrong[i]) {
            printf("%d ", i + 1);
        }
    }

    return 0;
}