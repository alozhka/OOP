#pragma once
#include <vector>

void ReadNumbers(std::istream& in, std::vector<double>& v);

void ProcessNumbers(std::vector<double>& v);

void PrintSortedNumbers(std::ostream& out, const std::vector<double>& v);
