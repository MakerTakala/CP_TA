#include "mycontrol.h"

int main() {
    initialize(0, 0, 0);
    counterclock_turn(M_PI /3);
    forward(3);
    print();
    clock_turn(M_PI / 3);
    forward(3);
    print();

    return 0;
}