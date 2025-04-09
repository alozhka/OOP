#include "../include/UnaryOperation.h"

UnaryOperation::UnaryOperation(std::function<double(double)> fn)
{
	m_fn = std::move(fn);
}

double UnaryOperation::Execute(double arg) const
{
	return m_fn(arg);
}

