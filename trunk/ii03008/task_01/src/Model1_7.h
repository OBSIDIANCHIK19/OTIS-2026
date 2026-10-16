#pragma once
#include "Model.h"

class Model1_7 : public Model {
private:
    double b1, b2, b3;
    double y_prev;
public:
    Model1_7(double a_val, double b1_val, double b2_val, double b3_val);
    double calculateStep(double u_current, double u_prev1, double u_prev2) override;
    void reset() override;
};
