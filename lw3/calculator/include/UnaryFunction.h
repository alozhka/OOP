#pragma once
#include "Function.h"
#include "UnaryOperation.h"

class UnaryFunction final : public Function
{
public:
	UnaryFunction(UnaryOperation op, std::shared_ptr<Expression> arg);
	[[nodiscard]] double GetResult() const override;

	~UnaryFunction() override = default;
private:
	const UnaryOperation m_op;
	const std::shared_ptr<Expression> m_arg;
};