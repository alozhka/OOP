#pragma once
#include "Expression.h"
#include "Operation.h"

class Function : public Expression
{
};

class BinaryFunction final : public Function
{
public:
	BinaryFunction(BinaryOperation  op, double arg1, double arg2);
	double GetResult() override;

private:
	const BinaryOperation m_op;
	double m_arg1;
	double m_arg2;
};