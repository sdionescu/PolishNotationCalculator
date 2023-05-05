#include <gtest/gtest.h>
#include "Calculator.hpp"

class CalculatorErrorSuite : public testing::TestWithParam<std::tuple<std::string, std::string>>
{
protected:
    Calculator m_sut{};
};

TEST_P(CalculatorErrorSuite, test_error) {
    auto invalidExpr = std::get<0>(GetParam());
    auto error       = std::get<1>(GetParam());
    auto errorMsg    = "Expression " + invalidExpr + " not valid! " + error;

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

INSTANTIATE_TEST_SUITE_P(
    TestErrorCases,
    CalculatorErrorSuite,
    testing::Values(
        std::make_tuple("/ * + 2 3 / + : 1 4 10", "Invalid char."),
        std::make_tuple("/ * + 2 3 // + 7 1 4 1", "Invalid char."),
        std::make_tuple("/ * + 2 / 3 / / 1 4 10", "Stack error."),
        std::make_tuple("/ * + 2 3 / + 7 1 4 0" , "Divide by 0 error.")));
