#include <iostream>
#include <string>
#include <vector>
/**
 * @brief      This class describes a Polish Notation (PN) calculator.
 */
class PNCalculator
{
public:
    /**
     * @brief      Gets the result of the given expression.
     *             For invalid PN format it throws an exception.
     *
     * @param[in]  expr  The PN expression
     *
     * @return     The result of the expression.
     */
    double getExprResult(const std::string& expr) const;

private:
    /**
     * @brief      { function_description }
     *
     * @param[in]  expr  The expression
     *
     * @return     { description_of_the_return_value }
     */
    std::vector<std::string> tokenizeExpr(const std::string& expr) const;
    /**
     * @brief      Returns the result of the operation.
     *             Valid operators:
     *                  + add
     *                  - subtract
     *                  * multiply
     *                  / divide
     *
     * @param[in]  oper  The operator
     * @param[in]  lhs   Left-hand side of operation 
     * @param[in]  rhs   Right-hand side of operation
     *
     * @return     The result of the operation.
     */
    double getResult(const char oper, const double lhs, const double rhs) const;
};
