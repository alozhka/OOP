#include "include/Calculator.h"
#include "include/CalculatorController.h"

#include <iostream>

int main()
{
	Calculator calculator;
	CalculatorController calculatorController(calculator, std::cin, std::cout);

	calculatorController.HandleInput();

	return 0;
}