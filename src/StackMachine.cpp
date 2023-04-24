#include <regex>
#include "StackMachine.hpp"

constexpr StackMachine::Operator OPERATOR_ADD      = '+';
constexpr StackMachine::Operator OPERATOR_SUBTRACT = '-';
constexpr StackMachine::Operator OPERATOR_MULTIPLY = '*';
constexpr StackMachine::Operator OPERATOR_DIVIDE   = '/';

constexpr int MIN_STACK_SIZE_VALID_OPERATION = 2;
constexpr int STACK_SIZE_VALID_RESULT = 1;

StackMachine::ErrorString StackMachine::execute(const std::string& entry)
{
	bool isOperand  = std::regex_match(entry, std::regex("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$"));
	bool isOperator = entry.size() == 1 &&
                        (entry[0] == OPERATOR_ADD ||
                         entry[0] == OPERATOR_SUBTRACT ||
                         entry[0] == OPERATOR_MULTIPLY ||
                         entry[0] == OPERATOR_DIVIDE);
    if (isOperand)
    {
        m_stack.push(std::stod(entry));
    }
    else if (isOperator)
    {
        if (m_stack.size() < MIN_STACK_SIZE_VALID_OPERATION)
        {
            return "Stack error.";
        }
        Operand lhs = m_stack.top(); m_stack.pop();
        Operand rhs = m_stack.top(); m_stack.pop();

        if (entry[0] == OPERATOR_DIVIDE && rhs == 0)
        {
            return "Divide by 0 error.";
        }
        Operand result = getOperationResult(entry[0], lhs, rhs);
        m_stack.push(result);
    }
    else
    {
        return "Invalid char.";
    }
    return {};
}

StackMachine::Operand StackMachine::getOperationResult(Operator operation, Operand lhs, Operand rhs) const
{
    Operand result = 0;
    switch (operation)
    {
        case OPERATOR_ADD:
            result = lhs + rhs;
            break;
        case OPERATOR_SUBTRACT:
            result = lhs - rhs;
            break;
        case OPERATOR_MULTIPLY:
            result = lhs * rhs;
            break;
        case OPERATOR_DIVIDE:
            result = lhs / rhs;
            break;
        default:
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