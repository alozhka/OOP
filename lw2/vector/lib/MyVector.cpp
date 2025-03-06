#include "MyVector.h"

#include <iomanip>
#include <iostream>

bool IsNumericString(const std::string &str)
{
	for (const char c : str)
	{
		if (!std::isdigit(c) && c != '.' && c != '-')
		{
			return false;
		}
	}
	return true;
}

void ReadNumbers(std::istream& in, std::vector<double>& numbers)
{
	std::string str;
	while (in >> str)
	{
		if (!IsNumericString(str))
		{
			throw std::invalid_argument("ERROR");
		}
		numbers.push_back(std::stod(str));
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

	std::ranges::transform(numbers, numbers.begin(), [max, min](double n) { return n * max / min; });
}

void SortNumbers(std::vector<double>& numbers)
{
	std::ranges::sort(numbers);
}

void PrintNumbers(std::ostream& out, const std::vector<double>& numbers)
{
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