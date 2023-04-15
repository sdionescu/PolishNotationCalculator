#include <stack>
#include <exception>
#include <stdexcept>
#include <regex>
#include <sstream>
#include "PNCalculator.hpp"

double PNCalculator::getExprResult(const std::string& expr) const
{
    std::stack<double> stack{};
    auto tokens = tokenizeExpr(expr);
    auto isOperator = [](const std::string& token) { return token == "+" || token == "-" || token == "*" || token == "/"; };
    auto isDouble = [](const std::string& token) { return std::regex_match(token, std::regex("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$")); };
    for (int i = tokens.size() - 1; i >= 0; i--)
    {
        auto token = tokens[i];
        if (isOperator(token))
        {
            if (stack.size() < 2)
            {
                std::string errorMsg = "Expression " + expr + " not valid!";
                throw std::invalid_argument(errorMsg);
            }
            double lhs = stack.top(); stack.pop();
            double rhs = stack.top(); stack.pop();
            double result = getResult(token[0], lhs, rhs);
            stack.push(result);
        }
        else if (isDouble(token))
        {
            stack.push(std::stod(token));
        }
        else
        {
            std::string errorMsg = "Expression " + expr + " not valid! Invalid char.";
            throw std::invalid_argument(errorMsg);
        }
    }
    if (stack.size() != 1)
    {
        std::string errorMsg = "Expression " + expr + " not valid!";
        throw std::invalid_argument(errorMsg);
    }
    return stack.top();
}

std::vector<std::string> PNCalculator::tokenizeExpr(const std::string& expr) const
{
    std::vector<std::string> output;
    std::istringstream ss(expr);
    std::string token;
    while(getline(ss, token, ' '))
    {
        output.push_back(token);
    }
    return output;
}

double PNCalculator::getResult(char oper, double lhs, double rhs) const
{
    double result = 0;
    switch (oper)
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
            // this cannot happen
            break;
    }
    return result;
}
