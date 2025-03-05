#include "MyVector.h"

#include <iostream>

void ReadNumbers(std::istream& in, std::vector<double>& v)
{
	double n;
	while (in >> n)
	{
		v.push_back(n);
	}
}
void ProcessNumbers(const std::vector<double>& v)
{
	throw std::invalid_argument("Not implemented");
}

void PrintSortedNumbers(std::ostream& out, const std::vector<double>& v)
{
	throw std::invalid_argument("Not implemented");
}