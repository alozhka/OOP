#include "../include/Calculator.h"

#include <stdexcept>

template <typename T>
	requires std::derived_from<T, Expression>
std::map<std::string, double> ListExpressionValues(const std::map<std::string, T>& map)
{
	std::map<std::string, double> results;

	for (const auto& [name, fn] : map)
	{
		results.emplace(name, fn.GetResult());
	}

	return results;
}

Calculator::Calculator() = default;

void Calculator::DefineVariable(std::string_view name, double value)
{
	if (m_variables.contains(name.data()) || m_functions.contains(name.data()))
	{
		throw std::runtime_error("Name already exists");
	}

	m_variables.emplace(std::string(name), value);
}

void Calculator::DefineFunction(std::string_view name, const Operation& op, std::string_view arg1, std::string_view arg2)
{
	const std::optional<Expression*> expr1 = GetExpression(arg1);
	const std::optional<Expression*> expr2 = GetExpression(arg2);
	auto fn = Function(op, expr1.value(), expr2.value());
	m_functions.emplace(std::string(name), std::move(fn));
}

double Calculator::GetValue(std::string_view name)
{
	return GetExpression(name).value()->GetResult();
}

void Calculator::SetValue(std::string_view name, double value)
{
	std::optional<Expression*> expr = GetExpression(name);

	if (!expr.has_value())
	{
		m_variables.emplace(std::string(name), value);
	}
	else
	{
		auto* var = dynamic_cast<Variable*>(expr.value());
		if (var == nullptr)
		{
			throw std::runtime_error("Cannot set value to function");
		}
		var->SetValue(value);
	}
}

void Calculator::SetValue(std::string_view name, std::string_view expressionName)
{
	std::optional<Expression*> destination = GetExpression(expressionName);
	if (!destination.has_value())
	{
		throw std::runtime_error("Name does not exist");
	}

	SetValue(name, destination.value()->GetResult());
}

std::map<std::string, double> Calculator::ListVariableValues() const
{
	return ListExpressionValues(m_variables);
}

std::map<std::string, double> Calculator::ListFunctionValues() const
{
	return ListExpressionValues(m_functions);
}

std::optional<Expression*> Calculator::GetExpression(std::string_view name)
{
	if (const auto varIt = m_variables.find(name.data()); varIt != m_variables.end())
	{
		return &varIt->second;
	}

	const auto fnIt = m_functions.find(name.data());
	if (fnIt == m_functions.end())
	{
		return std::nullopt;
	}

	return &fnIt->second;
}
