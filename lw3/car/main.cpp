#include "include/Car.h"
#include "include/CarController.h"

#include <iostream>

int main()
{
	Car car;
	const CarController carController(car, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		if (!carController.HandleCommand())
		{
			std::cout << "Unknown command!\n";
		}
	}

	return 0;
}