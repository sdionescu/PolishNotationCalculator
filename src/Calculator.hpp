#include <iostream>
#include <string>
#include <vector>
#include "StackMachine.hpp"

/**
 * @brief      This class describes a Polish Notation (PN) calculator.
 */
class Calculator
{
public:
    /**
     *  Type definitions
     */
    using Result = StackMachine::Result;
    /**
     * @brief      Returns the result of the given expression.
     *             For invalid PN format it throws an exception.
     *
     * @param[in]  expression  The PN expression
     *
     * @return     The result of the expression.
     */
    Result calculate(const std::string& expression) const;

private:
    /**
     * @brief      Split sting based on delimiter character
     *
     * @param[in]  expression  The expression
     * @param[in]  delimiter   The delimiter
     *
     * @return     Tokens
     */
    std::vector<std::string> tokenize(const std::string& expression, char delimiter) const;
};
