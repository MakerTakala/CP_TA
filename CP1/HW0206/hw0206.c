#include <stdint.h>
#include <stdio.h>

uint32_t ui = 0;
uint16_t us = 0;
int32_t si = -2;

int main() {
    int64_t r1 = (uint32_t)si;
    printf("%lld\n", r1);
}