#pragma once
#include "Expression.h"
#include "Operation.h"

class Function final : public Expression
{
public:
	Function(Operation  op, Expression* arg1, Expression* arg2);
	[[nodiscard]] double GetResult() const override;

private:
	const Operation m_op;
	Expression* m_arg1;
	Expression* m_arg2;
};