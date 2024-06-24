#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t a, b;
    printf("Please enter the first  number: ");
    scanf("%lld", &a);
    if (a < 0 || 2147483647 < a) {
        printf("Wrong input, your input must between 0 ~ 4294967295.\n");
        return 0;
    }
    printf("Please enter the second number: ");
    scanf("%lld", &b);
    if (b < 0 || 2147483647 < b) {
        printf("Wrong input, your input must between 0 ~ 4294967295.\n");
        return 0;
    }

    uint64_t c = (uint64_t)a * (uint64_t)b;

    uint64_t len_a = 0, len_b = 0, len_c = 0;
    if (a == 0) {
        len_a = 1;
    }
    for (uint64_t i = 1; i <= a; i *= 10) {
        len_a++;
        if (i == 10000000000UL) {
            if (a / i > 1) {
                len_a++;
            }
            break;
        }
    }
    if (b == 0) {
        len_b = 1;
    }
    for (uint64_t i = 1; i <= b; i *= 10) {
        len_b++;
        if (i == 10000000000UL) {
            if (b / i > 1) {
                len_b++;
            }
            break;
        }
    }
    if (c == 0) {
        len_c = 1;
    }
    for (uint64_t i = 1; i <= c; i *= 10) {
        len_c++;
        if (i == 10000000000000000000UL) {
            if (c / i > 1) {
                len_c++;
            }
            break;
        }
    }

    uint64_t max_len = len_a > len_b ? len_a : len_b;
    max_len = max_len > len_c ? max_len : len_c;

    // print a
    printf("  ");
    for (int i = 0; i < max_len - len_a; i++) {
        printf("  ");
    }
    if (a == 0) {
        printf("0\n");
    } else {
        uint64_t div_a = 1, tmp_a = a;
        for (int i = 0; i < len_a - 1; i++) {
            div_a *= 10;
        }
        for (int i = 0; i < len_a; i++) {
            printf("%lld ", tmp_a / div_a);
            tmp_a %= div_a;
            div_a /= 10;
        }
        printf("\n");
    }

    // print b
    printf("*)");
    for (int i = 0; i < max_len - len_b; i++) {
        printf("  ");
    }
    if (b == 0) {
        printf("0\n");
    } else {
        
        uint64_t div_b = 1, tmp_b = b;
        for (int i = 0; i < len_b - 1; i++) {
            div_b *= 10;
        }
        for (int i = 0; i < len_b; i++) {
            printf("%lld ", tmp_b / div_b);
            tmp_b %= div_b;
            div_b /= 10;
        }
        printf("\n");
    }
    
    //print line
    for (int i = 0; i < max_len * 2 + 1; i++) {
        printf("-");
    }
    printf("\n");

    if (len_b != 1 && c != 0) {
        uint64_t tmp_b = b;
        for (int i = 0; i < len_b; i++) {
            uint64_t d = (tmp_b % 10) * a, len_d = 0;
            if (d == 0) {
                len_d = 1;
            } else {
                for (uint64_t j = 1; j <= d; j *= 10) {
                    len_d++;
                    if (j == 10000000000UL) {
                        if (d / j > 1) {
                            len_d++;
                        }
                        break;
                    }
                }
            }

            // print middle
            printf("  ");
            for (int j = 0; j < max_len - len_d - i; j++) {
                printf("  ");
            }
            uint64_t div_d = 1;
            for (int j = 0; j < len_d - 1; j++) {
                div_d *= 10;
            }
            for (int j = 0; j < len_d; j++) {
                printf("%lld ", d / div_d);
                d %= div_d;
                div_d /= 10;
            }
            printf("\n");
            tmp_b /= 10;
        }

        //print line
        for (int i = 0; i < max_len * 2 + 1; i++) {
            printf("-");
        }
        printf("\n");
    }

    // print c
    printf("  ");
    for (int i = 0; i < max_len - len_c; i++) {
        printf("  ");
    }
    if (c == 0) {
        printf("0\n");
    } else {
        uint64_t div_c = 1, tmp_c = c;
        for (int i = 0; i < len_c - 1; i++) {
            div_c *= 10;
        }
        for (int i = 0; i < len_c; i++) {
            printf("%lld ", tmp_c / div_c);
            tmp_c %= div_c;
            div_c /= 10;
        }
        printf("\n");
    }

    return 0;
}