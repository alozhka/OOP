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

	void DefineBinaryFunction(const std::string& name, const BinaryOperation& op, Expression* arg1, Expression* arg2);
	double GetValue(const std::string& name);

private:
	std::map<std::string, Variable> m_variables;
	std::map<std::string, std::unique_ptr<Function>> m_functions;
};