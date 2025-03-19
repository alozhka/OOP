#include "lib/PrimeNumbers.h"
#include <iostream>

constexpr int MAX_UPPER_BOUND = 1'000'000;

struct Args
{
	int upperBound;
};

void PrintHelp()
{
	std::cerr << "Usage: prime_numbers.exe <upperBound>" << std::endl;
}

void ParseArgs(Args& args, int argc, char* argv[])
{
	int upperBound = std::stoi(argv[1]);

	if (0 < upperBound && upperBound <= MAX_UPPER_BOUND)
	{

	}
}

int main(const int argc, const char* argv[])
{
	if (argc != 2)
	{
		PrintHelp();
		return EXIT_FAILURE;
	}

	Args args;
	try
	{
		upperBound = std::stoi(argv[1]);
		if (upperBound < 0 || upperBound > 100000000)
		{
			std::cerr << "Upper bound must be between 0 and 100000000." << std::endl;
			return 1;
		}

		std::set<int> primes = GeneratePrimeNumbersSet(upperBound);

		for (int prime : primes)
		{
			std::cout << prime << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
