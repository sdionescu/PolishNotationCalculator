#include <iostream>
#include <string_view>
#include "Calculator.hpp"

constexpr std::string_view STOP_CMD = "S";

int main()
{
    auto calculator = Calculator();

    // test purpose only
    std::printf("Examples:\n");
    std::printf("/ 6 3 = %g\n", calculator.calculate("/ 6 3").value());
    std::printf("/ * + 23 / + 7 1 4 1 = %g\n", calculator.calculate("/ * + 2 3 / + 7 1 4 1").value());
    std::printf("/ * + 23 / + 7 1 4 10 = %g", calculator.calculate("/ * + 2 3 / + 7 1 4 10").value());

    while (true)
    {
        std::printf("\n\nPolish Notation: ");
        std::string expression{};
        std::getline(std::cin, expression);
        if (expression == STOP_CMD)
        {
            exit(0);
        }
        try
        {
            auto result = calculator.calculate(expression);
            std::printf("%s = ", expression.c_str());
            result ? std::printf("%g", result.value()) : std::printf("?");
        }
        catch (const std::invalid_argument& e)
        {
            std::printf("Please check your Polish Notation.\nError: %s", e.what());
        }
    }
    return 0;
}
