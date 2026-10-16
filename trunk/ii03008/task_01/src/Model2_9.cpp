#include "Model2_9.h"
#include <cmath>

Model2_9::Model2_9(double a_val, double b_val)
    : Model(a_val, "Model 2.9 (Square Root Modulated Action)"), b(b_val), y_prev(0.0) {
}

double Model2_9::calculateStep(double u_current, double u_prev1, double u_prev2) {
    (void)u_prev1;
    (void)u_prev2;
    // y_{\tau + 1} = a * y_{\tau} + b * \sqrt{|u_{\tau}|} * \text{sign}(u_{\tau})
    double sign_u = (u_current > 0) ? 1.0 : ((u_current < 0) ? -1.0 : 0.0);
    double y_next = a * y_prev + b * std::sqrt(std::abs(u_current)) * sign_u;
    y_prev = y_next;
    return y_next;
}

void Model2_9::reset() {
    y_prev = 0.0;
}