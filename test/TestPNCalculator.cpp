#include <gtest/gtest.h>
#include "PNCalculator.hpp"

class PNCalculatorSuite : public testing::TestWithParam<std::tuple<double, std::string>>
{
protected:
    PNCalculator m_sut{};
};

TEST_P(PNCalculatorSuite, test_expr_result) {
  auto output = std::get<0>(GetParam());
  auto input  = std::get<1>(GetParam());
  EXPECT_EQ(output, m_sut.getExprResult(input));
}

INSTANTIATE_TEST_SUITE_P(
    TwoOperandsOneOperator,
    PNCalculatorSuite,
    testing::Values(
      std::make_tuple(3, "+ 1 2"),
      std::make_tuple(2, "- 9 7"),
      std::make_tuple(6, "* 2 3"),
      std::make_tuple(2, "/ 6 3")));

INSTANTIATE_TEST_SUITE_P(
    ThreeOperandsTwoOperators,
    PNCalculatorSuite,
    testing::Values(
      std::make_tuple(10, "+ + 2 3 5"),
      std::make_tuple(1, "/ + 2 3 5"),
      std::make_tuple(-5, "- 5 * 2 5"),
      std::make_tuple(3.5, "+ / 5 2 1")));

INSTANTIATE_TEST_SUITE_P(
    ComplexExpression,
    PNCalculatorSuite,
    testing::Values(
      std::make_tuple(1, "/ * + 2 3 / + 7 1 4 10"),
      std::make_tuple(10, "/ * + 2 3 / + 7 1 4 1")));

TEST_F(PNCalculatorSuite, char_not_valid)
{
    std::string invalidExpr = "/ * + 2 3 / + : 1 4 10";
    std::string errorMsg = "Expression " + invalidExpr + " not valid! Invalid char.";
    EXPECT_THROW({
            try
            {
                m_sut.getExprResult(invalidExpr);
            }
            catch (const std::invalid_argument& e)
            {
                EXPECT_EQ(errorMsg, e.what());
                throw;
            }
        }, std::invalid_argument);
}

TEST_F(PNCalculatorSuite, too_many_operators)
{
    std::string invalidExpr = "/ * + 2 / 3 / / 1 4 10";
    std::string errorMsg = "Expression " + invalidExpr + " not valid!";
    EXPECT_THROW({
            try
            {
                m_sut.getExprResult(invalidExpr);
            }
            catch (const std::invalid_argument& e)
            {
                EXPECT_EQ(errorMsg, e.what());
                throw;
            }
        }, std::invalid_argument);
}

TEST_F(PNCalculatorSuite, too_many_operands)
{
    std::string invalidExpr = "/ * + 2 3 1 4 10";
    std::string errorMsg = "Expression " + invalidExpr + " not valid!";
    EXPECT_THROW({
            try
            {
                m_sut.getExprResult(invalidExpr);
            }
            catch (const std::invalid_argument& e)
            {
                EXPECT_EQ(errorMsg, e.what());
                throw;
            }
        }, std::invalid_argument);
}
