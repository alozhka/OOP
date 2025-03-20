#include "lib/Expression.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

int main()
{
	try
	{
		std::string line;
		while (std::getline(std::cin, line))
		{
			const int result = CalculateExpression(line);
			std::cout << result << std::endl;
		}
	}
	catch (const std::exception&)
	{
		std::cout << "ERROR" << std::endl;
	}

	return EXIT_SUCCESS;
}