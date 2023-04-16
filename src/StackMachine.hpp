#include <stack>
#include <string>

/**
 * @brief      This class implements the behavior of PN stack.
 */
class StackMachine
{
public:
    /**
     *  Type definitions
     */
    using Operand = double;
    using Operator = char;
    using ErrorString = std::optional<std::string>;
    using Result = std::optional<Operand>;
    /**
     * @brief      Updates the operators stack
     *
     * @param[in]  entry  The entry
     */
    ErrorString execute(const std::string& entry);
    /**
     * @brief      Get the result of PN expression
     *
     * @return     Result
     */
    Result result() const;

private:
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
    Operand getOperResult(const Operator oper, const Operand lhs, const Operand rhs) const;

private:
    std::stack<Operand> m_stack;
};