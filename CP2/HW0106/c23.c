#include <stdio.h>

int main() {
    
    _BitInt(8) a = -10;
    unsigned _BitInt(8) b = 20;
    printf("%lld\n", a - b);
    
    
    return 0;
}