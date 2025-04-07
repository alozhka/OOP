#include "../include/Calculator.h"

#include <stdexcept>

Calculator::Calculator() = default;

void Calculator::DefineVariable(std::string_view name, double value)
{
	if (m_variables.contains(name.data()))
	{
		throw std::runtime_error("Name already exists");
	}

	m_variables.emplace(std::string(name), value);
}

void Calculator::DefineFunction(std::string_view name, const Operation& op, std::string_view arg1, std::string_view arg2)
{
	Expression* expr1 = GetExpression(arg1);
	Expression* expr2 = GetExpression(arg2);
	auto fn = Function(op, expr1, expr2);
	m_functions.emplace(std::string(name), std::move(fn));
}

double Calculator::GetValue(std::string_view name)
{
	return GetExpression(name)->GetResult();
}

void Calculator::SetValue(std::string_view name, double value)
{
	Expression* expr = GetExpression(name);
	auto* var = dynamic_cast<Variable*>(expr);

	if (var == nullptr)
	{
		throw std::runtime_error("Invalid name");
	}

	var->SetValue(value);
}
std::map<std::string, double> Calculator::ListFunctionValues()
{
	std::map<std::string, double> results;

	for (auto& [name, fn] : m_functions)
	{
		results.emplace(name, fn.GetResult());
	}

	return results;
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

	return &fnIt->second;
}
