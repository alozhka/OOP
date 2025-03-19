#include "PrimeNumbers.h"
#include <cmath>
#include <ostream>
#include <vector>

constexpr int MAX_UPPER_BOUND = 100'000'000;

std::set<int> GeneratePrimeNumbersSet(const int upperBound)
{
	if (upperBound < 0 || upperBound > MAX_UPPER_BOUND)
	{
		throw std::invalid_argument("Upper bound must be between 0 and " + std::to_string(MAX_UPPER_BOUND));
	}

	std::set<int> primes;

	std::vector isPrime(upperBound + 1, true);
	for (int i = 2; i <= std::floor(std::sqrt(upperBound)); i++)
	{
		if (!isPrime[i])
		{
			continue;
		}

		int multiplier = 2;
		while (multiplier * i <= upperBound)
		{
			isPrime[multiplier * i] = false;
			multiplier++;
		}
	}

	for (int i = 2; i <= upperBound; i++)
	{
		if (isPrime[i])
		{
			primes.insert(i);
		}
	}

	return primes;
}

void PrintSet(std::ostream& out, const std::set<int>& set)
{
	for (const int el : set)
	{
		out << el << std::endl;
	}
}