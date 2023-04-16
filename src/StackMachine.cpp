#include <regex>
#include "StackMachine.hpp"

StackMachine::ErrorString StackMachine::execute(const std::string& entry)
{
	auto isOperand  = [](const std::string& token) { return std::regex_match(token, std::regex("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$")); };
	auto isOperator = [](const std::string& token) { return token == "+" || token == "-" || token == "*" || token == "/"; };

    if (isOperand(entry))
    {
        m_stack.push(std::stod(entry));
    }
    else if (isOperator(entry))
    {
        if (m_stack.size() < 2)
        {
            return "Stack error.";
        }
        Operand lhs = m_stack.top(); m_stack.pop();
        Operand rhs = m_stack.top(); m_stack.pop();
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
        case '+':
            result = lhs + rhs;
            break;
        case '-':
            result = lhs - rhs;
            break;
        case '*':
            result = lhs * rhs;
            break;
        case '/':
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
	if (m_stack.size() == 1)
    {
        return m_stack.top();
    }
    return {};
}