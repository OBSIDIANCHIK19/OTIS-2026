#pragma once
#include "Model.h"

class Model3_1 : public Model {
private:
    double y_current;
    double dt;
public:
    Model3_1(double a_val, double dt_val = 0.1);
    double calculateStep(double u_current, double u_prev1, double u_prev2) override;
    void reset() override;
};
