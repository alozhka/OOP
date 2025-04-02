#pragma once
#include "Expression.h"
#include "Operation.h"

class Function : public Expression
{
};

class BinaryFunction final : public Function
{
public:
	BinaryFunction(BinaryOperation  op, Expression* arg1, Expression* arg2);
	double GetResult() override;

private:
	const BinaryOperation m_op;
	Expression* m_arg1;
	Expression* m_arg2;
};