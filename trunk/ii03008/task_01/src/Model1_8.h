#pragma once
#include "Model.h"

class Model1_8 : public Model {
private:
    double a1, a2, b1, b2;
    double y_prev1, y_prev2;
public:
    Model1_8(double a1_val, double a2_val, double b1_val, double b2_val);
    double calculateStep(double u_current, double u_prev1, double u_prev2) override;
    void reset() override;
};