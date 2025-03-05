#include "MyVector.h"

#include <iomanip>
#include <iostream>

void ReadNumbers(std::istream& in, std::vector<double>& numbers)
{
	double n;
	while (in >> n)
	{
		numbers.push_back(n);
	}

	if (!in.eof() && in.fail())
	{
		throw std::invalid_argument("ERROR");
	}
}

void ProcessNumbers(std::vector<double>& numbers)
{
	if (numbers.empty())
	{
		return;
	}

	auto [minIterator, maxIterator] = std::minmax_element(numbers.begin(), numbers.end());
	const double min = *minIterator;
	const double max = *maxIterator;

	if (min == 0)
	{
		throw std::invalid_argument("ERROR");
	}

	for (size_t i = 0; i < numbers.size(); i++)
	{
		numbers[i] = numbers[i] * max / min;
	}
}

void PrintSortedNumbers(std::ostream& out, std::vector<double> numbers)
{
	std::ranges::sort(numbers);
	const size_t size = numbers.size();

	out << std::fixed << std::setprecision(3);
	for (size_t i = 0; i < size; i++)
	{
		out << numbers[i];
		if (i != size - 1)
		{
			out << " ";
		}
	}

	out << std::endl;
}