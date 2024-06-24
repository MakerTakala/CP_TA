#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int8_t digit;

int64_t state(int8_t event) {
    return (1<<(event - 1));
}

bool r1_success = false;
int64_t r1_state = 0b00000; //s5, s4, s3, s2, s1,
void rule1() {
    int64_t r1_new_state = 0b000000;
    if (digit == 1) {
        r1_new_state |= state(2);
    } 
    if (digit == 3) {
        r1_new_state |= state(1);
    }
    if (r1_state & state(1)) {
        if (digit == 1 || digit == 2) {
            r1_new_state |= state(2);
        } else if (digit == 3) {
            r1_new_state |= state(1);
        }
    }
    if (r1_state & state(2)) {
        if (digit == 6) {
            r1_new_state |= state(3);
        } else {
            r1_new_state |= state(2);
        }
    }
    if (r1_state & state(3)) {
        if (digit == 5) {
            r1_new_state |= state(4);
        } else if (digit == 6) {
            r1_new_state |= state(3);
        } else {
            r1_new_state |= state(2);
        }
    }
    if (r1_state & state(4)) {
        if (digit == 9) {
            r1_success = true;
        } else if (digit == 7) {
            r1_new_state |= state(5);
        } else {
            r1_new_state |= state(4);
        }
    }
    if (r1_state & state(5)) {
        if (digit == 8 || digit == 9) {
            r1_success = true;
        } else if (digit == 7) {
            r1_new_state |= state(5);
        } else {
            r1_new_state |= state(4);
        }
    }
    r1_state = r1_new_state;
}

bool r2_success = false;
int64_t r2_state = 0b000; //s3, s2, s1
void rule2() {
    int64_t r2_new_state = 0b0000;
    if (digit == 7) {
        r2_new_state |= state(1);
    }
    if (r2_state & state(1)) {
        if (digit == 7) {
            r2_new_state |= state(2);
        } else if (digit == 5) {
            r2_new_state |= state(3);
        } else if (digit == 3) {
            r2_success = true;
        } else {
            r2_new_state |= state(1);
        }
    }
    if (r2_state & state(2)) {
        if (digit == 5) {
            r2_new_state |= state(3);
        } else if (digit == 3) {
            r2_success = true;
        } else if (digit != 7) {
            r2_new_state |= state(2);
        }
    }
    if (r2_state & state(3)) {
        if (digit == 3) {
            r2_success = true;
        } else if (digit != 5) {
            r2_new_state |= state(3);
        }
    }
    r2_state = r2_new_state;
}

bool r3_success = false;
int64_t r3_state = 0b0000; //s4, s3, s2, s1
void rule3() {
    int64_t r3_new_state = 0b0000;
    if (digit == 4) {
        r3_new_state |= state(1);
    }
    if (r3_state & state(1)) {
        if (digit == 6) {
            r3_new_state |= state(2);
        } else {
            r3_new_state |= state(1);
        }
    }
    if (r3_state & state(2)) {
        if (digit == 6) {
            r3_new_state |= state(3);
        } else {
            r3_new_state |= state(1);
        }
    }
    if (r3_state & state(3)) {
        if (digit == 6) {
            r3_new_state |= state(4);
        } else {
            r3_new_state |= state(1);
        }
    }
    if (r3_state & state(4)) {
        if (digit == 8) {
            r3_success = true;
        } else {
            r3_new_state |= state(4);
        }
    }
    r3_state = r3_new_state;
}

int main() {
    while(1) {
        printf("Please input the digit: ");
        scanf("%hhd", &digit);
        if(digit == -1) break;
        rule1();
        rule2();
        rule3();
    }
    if (r1_success && r2_success && r3_success) {
        printf("SUCCESS!\n");
    } else {
        if (!r1_success) {
            printf("Rule 1 ");
        }
        if (!r2_success) {
            printf("Rule 2 ");
        }
        if (!r3_success) {
            printf("Rule 3 ");
        }
        printf("not follow!\n");
    }
    return 0;
}