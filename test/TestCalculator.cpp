#include <gtest/gtest.h>
#include "Calculator.hpp"

class CalculatorSuite : public testing::TestWithParam<std::tuple<double, std::string>>
{
protected:
    Calculator m_sut{};
};

TEST_P(CalculatorSuite, test_expr_result) {
  auto output = std::get<0>(GetParam());
  auto input  = std::get<1>(GetParam());
  EXPECT_EQ(output, m_sut.calculate(input));
}

INSTANTIATE_TEST_SUITE_P(
    TwoOperandsOneOperator,
    CalculatorSuite,
    testing::Values(
      std::make_tuple(3, "+ 1 2"),
      std::make_tuple(2, "- 9 7"),
      std::make_tuple(6, "* 2 3"),
      std::make_tuple(2, "/ 6 3")));

INSTANTIATE_TEST_SUITE_P(
    ThreeOperandsTwoOperators,
    CalculatorSuite,
    testing::Values(
      std::make_tuple(10, "+ + 2 3 5"),
      std::make_tuple(1, "/ + 2 3 5"),
      std::make_tuple(-5, "- 5 * 2 5"),
      std::make_tuple(3.5, "+ / 5 2 1")));

INSTANTIATE_TEST_SUITE_P(
    ComplexExpression,
    CalculatorSuite,
    testing::Values(
      std::make_tuple(1, "/ * + 2 3 / + 7 1 4 10"),
      std::make_tuple(10, "/ * + 2 3 / + 7 1 4 1")));
