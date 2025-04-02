#pragma once
#include <functional>

class UnaryOperation
{
public:
	explicit UnaryOperation(std::function<double(double)> fn);
	[[nodiscard]] double Execute(double arg) const;

private:
	std::function<double(double)> m_fn;
};

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
const BinaryOperation SUB([](double a, double b) { return a - b; });
} // namespace Operations