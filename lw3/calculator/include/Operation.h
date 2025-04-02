#pragma once
#include <functional>
#include <cmath>

class Operation
{
public:
	explicit Operation(std::function<double(double, double)> fn);
	[[nodiscard]] double Execute(double arg1, double arg2) const;

private:
	std::function<double(double, double)> m_fn;
};

namespace Operations
{
const Operation SUM([](double a, double b) { return a + b; });
const Operation SUBTRACT([](double a, double b) { return a - b; });
const Operation MULTIPLY([](double a, double b) { return a * b; });
const Operation DIVIDE([](double a, double b) { return b == 0 ? std::nan("") : a / b; });
} // namespace Operations