#pragma once
#include "Expression.h"

class Function : public Expression
{
public:
	[[nodiscard]] double GetResult() const override = 0;
};