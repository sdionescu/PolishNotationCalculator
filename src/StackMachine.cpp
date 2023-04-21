#include <regex>
#include "StackMachine.hpp"

constexpr StackMachine::Operator OPER_ADD      = '+';
constexpr StackMachine::Operator OPER_SUBTRACT = '-';
constexpr StackMachine::Operator OPER_MULTIPLY = '*';
constexpr StackMachine::Operator OPER_DIVIDE   = '/';

constexpr int MIN_STACK_SIZE_VALID_OPERATION = 2;
constexpr int STACK_SIZE_VALID_RESULT = 1;

StackMachine::ErrorString StackMachine::execute(const std::string& entry)
{
	bool isOperand  = std::regex_match(entry, std::regex("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$"));
	bool isOperator = entry.size() == 1 &&
                        (entry[0] == OPER_ADD ||
                         entry[0] == OPER_SUBTRACT ||
                         entry[0] == OPER_MULTIPLY ||
                         entry[0] == OPER_DIVIDE);
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