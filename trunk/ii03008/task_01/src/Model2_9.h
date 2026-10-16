#pragma once
#include "Model.h"

class Model2_9 : public Model {
private:
    double b;
    double y_prev;
public:
    Model2_9(double a_val, double b_val);
    double calculateStep(double u_current, double u_prev1, double u_prev2) override;
    void reset() override;
};
