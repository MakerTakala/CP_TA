#include "mycontrol.h"

static double character_x, character_y, character_a;
static bool initialized = false;

void initialize( double x, double y, double a) {
    character_x = x;
    character_y = y;
    character_a = a;

    initialized = true;
}

int32_t forward( double length ) {
    if (!initialized) {
        return -1;
    }

    character_x += length * cos(character_a);
    character_y += length * sin(character_a);

    return 0;
}

int32_t clock_turn( double x ) {
    if (!initialized) {
        return -1;
    }

    character_a -= x;

    return 0;
}

int32_t counterclock_turn( double x ) {
    if (!initialized) {
        return -1;
    }

    character_a += x;

    return 0;
}

int32_t print() {
    if (!initialized) {
        return -1;
    }

    while (character_a >= 2 * M_PI) {
        character_a -= 2 * M_PI;
    }
    while (character_a < 0) {
        character_a += 2 * M_PI;
    }

    printf("position: (%.2lf,%.2lf), angle: %.2lf\n", round(character_x * 100.0)/100.0, round(character_y * 100.0)/100.0, round(character_a / M_PI * 100.0)/100.0);

    return 0;
}