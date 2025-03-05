#include "lib/MyVector.h"

#include <iostream>

int main()
{
	std::vector<double> numbers{};

	try
	{
		ReadNumbers(std::cin, numbers);
		ProcessNumbers(numbers);
		PrintSortedNumbers(std::cout, numbers);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		// всегда возвращаем 0 для Yandex Contest
	}

	return 0;
}
