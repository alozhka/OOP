#include <utility>

#include "../include/Function.h"

BinaryFunction::BinaryFunction(BinaryOperation op, double arg1, double arg2)
	: m_op(std::move(op))
	, m_arg1(arg1)
	, m_arg2(arg2)
{
}

double BinaryFunction::GetResult()
{
	return m_op.Execute(m_arg1, m_arg2);
}
