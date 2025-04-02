#include "../include/Calculator.h"

#include <stdexcept>

Calculator::Calculator() = default;

void Calculator::DefineVariable(std::string_view name, double value)
{
	if (m_variables.contains(name.data()))
	{
		throw std::runtime_error("Name already exists");
	}

	m_variables.emplace(name.data(), value);
}

void Calculator::DefineBinaryFunction(std::string_view name, const BinaryOperation& op, std::string_view arg1, std::string_view arg2)
{
	Expression* expr1 = GetExpression(arg1);
	Expression* expr2 = GetExpression(arg2);
	m_functions[name.data()] = std::make_unique<BinaryFunction>(op, expr1, expr2);
}

double Calculator::GetValue(std::string_view name)
{
	return GetExpression(name)->GetResult();
}

Expression* Calculator::GetExpression(std::string_view name)
{
	if (const auto varIt = m_variables.find(name.data()); varIt != m_variables.end())
	{
		return &varIt->second;
	}

	const auto fnIt = m_functions.find(name.data());
	if (fnIt == m_functions.end())
	{
		throw std::runtime_error("Name does not exists");
	}

	return fnIt->second.get();
}
