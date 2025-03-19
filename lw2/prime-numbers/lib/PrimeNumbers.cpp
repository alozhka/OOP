#include "PrimeNumbers.h"
#include <cmath>
#include <vector>

std::set<int> GeneratePrimeNumbersSet(const int upperBound)
{
	std::set<int> primes;
	if (upperBound < 0)
	{
		return primes;
	}

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
