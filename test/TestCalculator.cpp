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

TEST_F(CalculatorSuite, char_not_valid_error)
{
    // only + - * / are valid operands
    std::string invalidExpr = "/ * + 2 3 / + : 1 4 10";
    std::string errorMsg = "Expression " + invalidExpr + " not valid! Invalid char.";
    EXPECT_THROW({
            try
            {
                m_sut.calculate(invalidExpr);
            }
            catch (const std::invalid_argument& e)
            {
                EXPECT_EQ(errorMsg, e.what());
                throw;
            }
        }, std::invalid_argument);

    // duplicated operand is not allowed e.g. //
    invalidExpr = "/ * + 2 3 // + 7 1 4 1";
    errorMsg = "Expression " + invalidExpr + " not valid! Invalid char.";
    EXPECT_THROW({
            try
            {
                m_sut.calculate(invalidExpr);
            }
            catch (const std::invalid_argument& e)
            {
                EXPECT_EQ(errorMsg, e.what());
                throw;
            }
        }, std::invalid_argument);
}

TEST_F(CalculatorSuite, too_many_operators_error)
{
    std::string invalidExpr = "/ * + 2 / 3 / / 1 4 10";
    std::string errorMsg = "Expression " + invalidExpr + " not valid! Stack error.";
    EXPECT_THROW({
            try
            {
                m_sut.calculate(invalidExpr);
            }
            catch (const std::invalid_argument& e)
            {
                EXPECT_EQ(errorMsg, e.what());
                throw;
            }
        }, std::invalid_argument);
}

TEST_F(CalculatorSuite, too_many_operands_error)
{
    std::string invalidExpr = "/ * + 2 3 1 4 10";
    std::string errorMsg = "Expression " + invalidExpr + " not valid! Result error.";
    EXPECT_THROW({
            try
            {
                m_sut.calculate(invalidExpr);
            }
            catch (const std::invalid_argument& e)
            {
                EXPECT_EQ(errorMsg, e.what());
                throw;
            }
        }, std::invalid_argument);
}

TEST_F(CalculatorSuite, divide_by_zero_error)
{
    std::string invalidExpr = "/ * + 2 3 / + 7 1 4 0";
    std::string errorMsg = "Expression " + invalidExpr + " not valid! Divide by 0 error.";
    EXPECT_THROW({
            try
            {
                m_sut.calculate(invalidExpr);
            }
            catch (const std::invalid_argument& e)
            {
                EXPECT_EQ(errorMsg, e.what());
                throw;
            }
        }, std::invalid_argument);
}
