#include "lib/Expression.h"

#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		try
		{
			const int result = CalculateExpression(line);
			std::cout << result << std::endl;
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << "ERROR" << std::endl;
		}
	}
	return 0;
}