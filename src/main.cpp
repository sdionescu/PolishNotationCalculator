#include <iostream>
#include "PNCalculator.hpp"

int main()
{
    auto calculator = PNCalculator();
    std::cout << "/ 6 3 = " << calculator.getExprResult("/ 6 3") << '\n';
    std::cout << "/ * + 23 / + 7 1 4 1 = " << calculator.getExprResult("/ * + 2 3 / + 7 1 4 1") << '\n';
    std::cout << "/ * + 23 / + 7 1 4 10 = " << calculator.getExprResult("/ * + 2 3 / + 7 1 4 10") << '\n';
}
