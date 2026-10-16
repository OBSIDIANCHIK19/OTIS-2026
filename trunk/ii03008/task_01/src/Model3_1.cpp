#include "Model3_1.h"

Model3_1::Model3_1(double a_val, double dt_val)
    : Model(a_val, "Model 3.1 (Pure Linear Decay)"), y_current(10.0), dt(dt_val) {
}

double Model3_1::calculateStep(double u_current, double u_prev1, double u_prev2) {
    (void)u_prev1;
    (void)u_prev2;
    // dy/dt = -a * y + u_current
    double dy = (-a * y_current + u_current) * dt;
    y_current += dy;
    return y_current;
}

void Model3_1::reset() {
    y_current = 10.0;
}