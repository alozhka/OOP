#pragma once
#include "Function.h"
#include "Operation.h"
#include "Variable.h"
#include <map>
#include <memory>

class Calculator
{
public:
	Calculator();

	void DefineVariable(std::string_view name, double value);
	void DefineBinaryFunction(std::string_view name, const Operation& op, std::string_view arg1, std::string_view arg2);

	double GetValue(std::string_view name);

private:
	Expression* GetExpression(std::string_view name);

	std::map<std::string, Variable> m_variables;
	std::map<std::string, Function> m_functions;
};