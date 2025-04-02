#include "../include/Calculator.h"

#include <stdexcept>

Calculator::Calculator() = default;

void Calculator::DefineBinaryFunction(const std::string& name, const BinaryOperation& op, Expression* arg1, Expression* arg2)
{
	m_functions[name] = std::make_unique<BinaryFunction>(op, arg1, arg2);
}

double Calculator::GetValue(const std::string& name)
{
	const auto value = m_functions.find(name);

	if (value == m_functions.end())
	{
		throw std::runtime_error("Such function does not exists");
	}

	Function* function = value->second.get();
	return function->GetResult();
}
