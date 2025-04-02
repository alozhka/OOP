#pragma once
#include "../include/Variable.h"
#include "Expression.h"

class Variable final : public Expression
{
public:
	explicit Variable(double value);
	double GetResult() override;

private:
	double m_value;
};
