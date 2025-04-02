#include <utility>

#include "../include/Function.h"

Function::Function(Operation op, Expression* arg1, Expression* arg2)
	: m_op(std::move(op))
	, m_arg1(arg1)
	, m_arg2(arg2)
{
}

double Function::GetResult()
{
	return m_op.Execute(m_arg1->GetResult(), m_arg2->GetResult());
}
