#include "../include/UnaryFunction.h"

UnaryFunction::UnaryFunction(UnaryOperation op, Expression* arg)
	: m_op(std::move(op))
	, m_arg(arg)
{
}

double UnaryFunction::GetResult() const
{
	return m_op.Execute(m_arg->GetResult());
}

