#include <utility>

#include "../include/BinaryFunction.h"

BinaryFunction::BinaryFunction(BinaryOperation op, Expression* arg1, Expression* arg2)
	: m_op(std::move(op))
	, m_arg1(arg1)
	, m_arg2(arg2)
{
}

double BinaryFunction::GetResult() const
{
	return m_op.Execute(m_arg1->GetResult(), m_arg2->GetResult());
}
