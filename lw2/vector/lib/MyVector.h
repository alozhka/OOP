#pragma once
#include <vector>

void ReadNumbers(std::istream& in, std::vector<double>& numbers);

void ProcessNumbers(std::vector<double>& numbers);

void SortNumbers(std::vector<double>& numbers);

void PrintNumbers(std::ostream& out, const std::vector<double>& numbers);