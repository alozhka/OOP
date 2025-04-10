#pragma once
#include "BinaryOperation.h"
#include "Expression.h"
#include "Function.h"

class BinaryFunction final : public Function
{
public:
	BinaryFunction(BinaryOperation op, std::shared_ptr<Expression> arg1, std::shared_ptr<Expression> arg2);
	[[nodiscard]] double GetResult() const override;

	~BinaryFunction() override = default;
private:
	const BinaryOperation m_op;
	std::shared_ptr<Expression> m_arg1;
	std::shared_ptr<Expression> m_arg2;
};