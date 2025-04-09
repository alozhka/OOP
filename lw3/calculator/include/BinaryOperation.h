#pragma once
#include <functional>
#include <cmath>

class BinaryOperation
{
public:
	explicit BinaryOperation(std::function<double(double, double)> fn);
	[[nodiscard]] double Execute(double arg1, double arg2) const;

private:
	std::function<double(double, double)> m_fn;
};

namespace Operations
{
const BinaryOperation SUM([](double a, double b) { return a + b; });
const BinaryOperation SUBTRACT([](double a, double b) { return a - b; });
const BinaryOperation MULTIPLY([](double a, double b) { return a * b; });
const BinaryOperation DIVIDE([](double a, double b) { return b == 0 ? std::nan("") : a / b; });
} // namespace Operations