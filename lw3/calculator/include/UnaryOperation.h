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

namespace Operations::Unary
{
const UnaryOperation IDENTITY([](double arg) { return arg; });
} // namespace Operations::Unary