#include "MyVector.h"

#include <iostream>

void ReadNumbers(std::istream& in, std::vector<double>& v)
{
	double n;
	while (in >> n)
	{
		v.push_back(n);
	}

	if (!in.eof() && in.fail())
	{
		throw std::invalid_argument("ERROR");
	}
}

void ProcessNumbers(std::vector<double>& v)
{
	if (v.empty())
	{
		return;
	}

	auto [minIterator, maxIterator] = std::minmax_element(v.begin(), v.end());
	const double min = *minIterator;
	const double max = *maxIterator;

	if (min == 0)
	{
		throw std::invalid_argument("ERROR");
	}

	for (size_t i = 0; i < v.size(); i++)
	{
		v[i] = v[i] * max / min;
	}
}

void PrintSortedNumbers(std::ostream& out, const std::vector<double>& v)
{
	throw std::invalid_argument("Not implemented");
}