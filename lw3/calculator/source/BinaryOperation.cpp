#include "../include/BinaryOperation.h"

BinaryOperation::BinaryOperation(std::function<double(double, double)> fn)
{
	m_fn = std::move(fn);
}

double BinaryOperation::Execute(double arg1, double arg2) const
{
	return m_fn(arg1, arg2);
}
