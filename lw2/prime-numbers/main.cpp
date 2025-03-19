#include "lib/PrimeNumbers.h"
#include <iostream>
#include <string>

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
