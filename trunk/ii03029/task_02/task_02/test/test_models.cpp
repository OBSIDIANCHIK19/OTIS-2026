#include <gtest/gtest.h>
#include "Model_1_8.h"

using namespace std;

TEST(LinearModelTest, ConstantInput) {
    double y0 = 1.0;
    double u = 1.0;
    double a = 0.5;
    double b = 0.5;

    EXPECT_NEAR(simulateLinear(y0, u, a, b, 1), 1.0, 1e-6);
    EXPECT_NEAR(simulateLinear(y0, u, a, b, 2), 1.0, 1e-6);
    EXPECT_NEAR(simulateLinear(y0, u, a, b, 3), 1.0, 1e-6);
}

TEST(LinearModelTest, UnstableGrowth) {
    double y0 = 1.0;
    double u = 1.0;
    double a = 2.0;
    double b = 1.0;

    EXPECT_NEAR(simulateLinear(y0, u, a, b, 1), 3.0, 1e-6);
    EXPECT_NEAR(simulateLinear(y0, u, a, b, 2), 7.0, 1e-6);
    EXPECT_NEAR(simulateLinear(y0, u, a, b, 3), 15.0, 1e-6);
}