#include "lib/PrimeNumbers.h"
#include <iostream>
#include <string>

constexpr int MAX_UPPER_BOUND = 100'000'000;

struct Args
{
	int upperBound;
};

void PrintHelp()
{
	std::cerr << "Usage: prime_numbers.exe <upperBound>" << std::endl;
}

void ParseArgs(Args& args, const char* argv[])
{
	const int upperBound = std::stoi(argv[1]);

	if (upperBound < 0 || upperBound > MAX_UPPER_BOUND)
	{
		throw std::invalid_argument("Upper bound must be between 0 and " + std::to_string(MAX_UPPER_BOUND));
	}

	args.upperBound = upperBound;
}

int main(const int argc, const char* argv[])
{
	if (argc != 2)
	{
		PrintHelp();
		return EXIT_FAILURE;
	}

	try
	{
		Args args{};
		ParseArgs(args, argv);
		const std::set<int> primes = GeneratePrimeNumbersSet(args.upperBound);
		PrintSet(std::cout, primes);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
