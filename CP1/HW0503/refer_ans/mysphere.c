#include "mysphere.h"

int32_t get_cap_area( double r, double a, double b, double c, double d, double *pArea ) {
    if (pArea == NULL) {
        return -1;
    }
    if (r <= 0 || (a == 0 && b == 0 && c == 0)) {
        return -1;
    }

    double h = fabs(d) / sqrt(a * a + b * b + c * c) ;
    if (h >= r) {
        return 0;
    }
    
    *pArea = M_PI * (r * r - h * h);
    return 1;
}