#pragma once

inline double simulateLinear(double y0, double u, double a, double b, int steps) {
    double y = y0;
    for (int i = 0; i < steps; ++i) {
        y = a * y + b * u;
    }
    return y;
}