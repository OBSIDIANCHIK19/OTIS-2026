#pragma once
#include "Model.h"

class Model2_10 : public Model {
private:
    double b_coef;
    double y_prev;
public:
    Model2_10(double a_val, double b_val);
    double calculateStep(double u_current, double u_prev1, double u_prev2) override;
    void reset() override;
};