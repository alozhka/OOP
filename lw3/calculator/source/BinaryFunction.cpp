#include <utility>

#include "../include/BinaryFunction.h"

BinaryFunction::BinaryFunction(BinaryOperation op, std::shared_ptr<Expression> arg1, std::shared_ptr<Expression> arg2)
	: m_op(std::move(op))
	, m_arg1(std::move(arg1))
	, m_arg2(std::move(arg2))
{
}

double BinaryFunction::GetResult() const
{
	return m_op.Execute(m_arg1->GetResult(), m_arg2->GetResult());
}
