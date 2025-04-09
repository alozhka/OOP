#pragma once
#include "Function.h"
#include "UnaryOperation.h"

class UnaryFunction final : public Function
{
public:
	UnaryFunction(UnaryOperation op, Expression* arg);
	[[nodiscard]] double GetResult() const override;

private:
	const UnaryOperation m_op;
	const Expression* m_arg;
};