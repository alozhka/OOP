#pragma once
#include <vector>

void ReadNumbers(std::istream& in, std::vector<double>& numbers);

void ProcessNumbers(std::vector<double>& numbers);

void PrintSortedNumbers(std::ostream& out, std::vector<double> numbers);
