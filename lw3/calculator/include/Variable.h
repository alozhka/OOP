#pragma once
#include "../include/Variable.h"
#include "Expression.h"

class Variable final : public Expression
{
public:
	explicit Variable(double value);

	[[nodiscard]] double GetResult() const override;
	void SetValue(double value);

private:
	double m_value;
};
