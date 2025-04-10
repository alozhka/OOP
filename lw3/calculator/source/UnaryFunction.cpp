#include <utility>

#include "../include/UnaryFunction.h"

UnaryFunction::UnaryFunction(UnaryOperation op, std::shared_ptr<Expression> arg)
	: m_op(std::move(op))
	, m_arg(std::move(arg))
{
}

double UnaryFunction::GetResult() const
{
	return m_op.Execute(m_arg->GetResult());
}

