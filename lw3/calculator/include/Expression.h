#pragma once

class Expression
{
public:
	[[nodiscard]] virtual double GetResult() const = 0;

	virtual ~Expression() = default;
};