#pragma once
#include "BinaryOperation.h"
#include "Expression.h"
#include "Function.h"

class BinaryFunction final : public Function
{
public:
	BinaryFunction(BinaryOperation op, Expression* arg1, Expression* arg2);
	[[nodiscard]] double GetResult() const override;

private:
	const BinaryOperation m_op;
	Expression* m_arg1;
	Expression* m_arg2;
};