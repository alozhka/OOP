#include "../include/Operation.h"

UnaryOperation::UnaryOperation(std::function<double(double)> fn)
{
	m_fn = fn;
}

double UnaryOperation::Execute(double arg) const
{
	return m_fn(arg);
}

BinaryOperation::BinaryOperation(std::function<double(double, double)> fn)
{
	m_fn = fn;
}

double BinaryOperation::Execute(double arg1, double arg2) const
{
	return m_fn(arg1, arg2);
}
