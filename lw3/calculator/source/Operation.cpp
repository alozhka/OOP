#include <utility>

#include "../include/Operation.h"

Operation::Operation(std::function<double(double, double)> fn)
{
	m_fn = std::move(fn);
}

double Operation::Execute(double arg1, double arg2) const
{
	return m_fn(arg1, arg2);
}
