#pragma once
#include <string>

enum class InputType {
    Step,       // Стуенчатое (u_tau = const)
    Impulse,    // Импульсное (u_0 = 1, u_{tau>0} = 0)
    Harmonic    // Гармоническое (u_tau = sin(tau))
};

class Model {
protected:
    double a;
    std::string name;
public:
    Model(double a_val, std::string model_name) : a(a_val), name(model_name) {}
    virtual ~Model() = default;

    virtual double calculateStep(double u_current, double u_prev1, double u_prev2) = 0;
    virtual void reset() = 0;

    std::string getName() const { return name; }
    double getParameterA() const { return a; }
};
