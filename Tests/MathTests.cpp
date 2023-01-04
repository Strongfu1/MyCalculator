#include <gtest/gtest.h>

#include "../MathCalc/Model/MathModel.h"

s21::MathModel model;

#define MKTEST(groupname, name, str, res, x)                                   \
  TEST(groupname, name) {                                                      \
    ASSERT_FLOAT_EQ(model.Calculation(                                         \
                        model.PolishNotation(model.RemoveUnaryMinus(str)), x), \
                    res);                                                      \
  }
MKTEST(simple, plus, "2+2", 4, 0);

MKTEST(simple, minus, "2-2", 0, 0);

MKTEST(simple, mul, "2*2", 4, 0);

MKTEST(simple, div, "2/2", 1, 0);

MKTEST(simple, mod, "123%2", 1, 0);

MKTEST(simple, power, "5^2", 25, 0);

MKTEST(simple, func, "cos(0)", 1, 0);

MKTEST(hard, parenthesis, "5+(2^3+16)*10/(20*10)", 6.2, 0);

MKTEST(hard, unarminus, "-(-(-(-(22-11+5))))", 16, 0);

MKTEST(hard, funcs, "sin(10*(-(20*sqrt(25.666+atan(0.2)/0.11^3))))", 0.8233867,
       0);

MKTEST(hard, more_funcs, "log(33333)*sin(22)/ln(223523)+tan(0.2)", 0.1994598,
       0);

MKTEST(hard, x, "x^sin(10*(x-(20*sqrt(25.666+atan(x)/0.11^3))))", 0.073789246,
       15);

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}