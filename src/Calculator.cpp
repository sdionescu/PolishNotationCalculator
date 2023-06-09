#include <exception>
#include <stdexcept>
#include <sstream>
#include "Calculator.hpp"

constexpr char DELIMITER = ' ';

Calculator::Result Calculator::calculate(const std::string& expression) const
{
    StackMachine stackMachine;
    StackMachine::ErrorString error{};

    auto tokens = tokenize(expression, DELIMITER);
    for (int i = tokens.size() - 1; i >= 0 && !error; i--)
    {
        error = stackMachine.execute(tokens[i]);
    }
    if (error)
    {
        throw std::invalid_argument("Expression " + expression + " not valid! " + *error);
    }

    auto result = stackMachine.result();
    if (!result)
    {
        throw std::invalid_argument("Expression " + expression + " not valid! Result error.");
    }
    return result;
}

std::vector<std::string> Calculator::tokenize(const std::string& expression, char delimiter) const
{
    std::string token{};
    std::vector<std::string> output{};
    std::istringstream ss(expression);

    while(getline(ss, token, delimiter))
    {
        output.push_back(token);
    }
    return output;
}
