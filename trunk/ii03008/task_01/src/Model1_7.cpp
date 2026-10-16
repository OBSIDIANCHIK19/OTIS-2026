#include "Model1_7.h"

Model1_7::Model1_7(double a_val, double b1_val, double b2_val, double b3_val)
    : Model(a_val, "Model 1.7 (Multi-Step Control History)"), b1(b1_val), b2(b2_val), b3(b3_val), y_prev(0.0) {
}

double Model1_7::calculateStep(double u_current, double u_prev1, double u_prev2) {
    // y_{\tau + 1} = a * y_{\tau} + b_1 * u_{\tau} + b_2 * u_{\tau - 1} + b_3 * u_{\tau - 2}
    double y_next = a * y_prev + b1 * u_current + b2 * u_prev1 + b3 * u_prev2;
    y_prev = y_next;
    return y_next;
}

void Model1_7::reset() {
    y_prev = 0.0;
}