#include "engine.h"

double modulo_R(double x, double q) {
    double y = 0;
    while (y<abs_double(x)) {
        y += q;
    }
    
    if (x>=0) {
        return abs_double(x) - y + q;
    }
    else {
        return abs_double(abs_double(x) - y);
    }
}

double affine_modulo(double a, double b, double q, double x) {
    return modulo_R((a*x+b), q);
}