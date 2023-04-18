#include <regex>
#include "StackMachine.hpp"

constexpr StackMachine::Operator OPER_ADD      = '+';
constexpr StackMachine::Operator OPER_SUBTRACT = '-';
constexpr StackMachine::Operator OPER_MULTIPLY = '*';
constexpr StackMachine::Operator OPER_DIVIDE   = '/';

// PN stack should contain at least two
// operands in order to perform an opeartion
constexpr int MIN_STACK_SIZE_VALID_OPERATION = 2;
// PN stack should have at the end of the execution
// just one entry representing the result of the PN
constexpr int STACK_SIZE_VALID_RESULT = 1;

StackMachine::ErrorString StackMachine::execute(const std::string& entry)
{
	auto isOperand  = [](const std::string& token) {
        return std::regex_match(token, std::regex("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$")); };
	auto isOperator = [](const std::string& token) { 
        return token.size() == 1 &&
                (token[0] == OPER_ADD ||
                 token[0] == OPER_SUBTRACT ||
                 token[0] == OPER_MULTIPLY ||
                 token[0] == OPER_DIVIDE); };

    if (isOperand(entry))
    {
        m_stack.push(std::stod(entry));
    }
    else if (isOperator(entry))
    {
        if (m_stack.size() < MIN_STACK_SIZE_VALID_OPERATION)
        {
            return "Stack error.";
        }
        Operand lhs = m_stack.top(); m_stack.pop();
        Operand rhs = m_stack.top(); m_stack.pop();

        // divide by 0 not allowed
        if (entry[0] == '/' && rhs == 0)
        {
            return "Divide by 0 error.";
        }
        Operand result = getOperResult(entry[0], lhs, rhs);
        m_stack.push(result);
    }
    else
    {
        return "Invalid char.";
    }
    return {};
}

StackMachine::Operand StackMachine::getOperResult(Operator operation, Operand lhs, Operand rhs) const
{
    Operand result = 0;
    switch (operation)
    {
        case OPER_ADD:
            result = lhs + rhs;
            break;
        case OPER_SUBTRACT:
            result = lhs - rhs;
            break;
        case OPER_MULTIPLY:
            result = lhs * rhs;
            break;
        case OPER_DIVIDE:
            result = lhs / rhs;
            break;
        default:
            // cannot happen
            break;
    }
    return result;
}

StackMachine::Result StackMachine::result() const
{
	if (m_stack.size() == STACK_SIZE_VALID_RESULT)
    {
        return m_stack.top();
    }
    return {};
}