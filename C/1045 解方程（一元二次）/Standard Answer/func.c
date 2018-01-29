#include <math.h>
int getRoots(double a, double b, double c, \
double *pRootOne, double *pRootTwo) {
    double delta = b * b - 4.0 * a * c;
    if (delta < 0) {
        return 0;
    } else {
        *pRootOne = (-b + sqrt(delta)) / (2.0 * a);
        *pRootTwo = (-b - sqrt(delta)) / (2.0 * a);
        return 1;
    }
}
