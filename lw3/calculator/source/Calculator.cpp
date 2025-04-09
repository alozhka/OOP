#include "../include/Calculator.h"
#include "../include/BinaryFunction.h"
#include "../include/UnaryFunction.h"

#include <stdexcept>

Calculator::Calculator() = default;

void Calculator::DefineVariable(std::string_view name, double value)
{
	if (m_variables.contains(name.data()) || m_functions.contains(name.data()))
	{
		throw std::runtime_error("Name already exists");
	}

	m_variables.emplace(std::string(name), value);
}
void Calculator::DefineUnaryFunction(std::string_view name, const UnaryOperation& op, std::string_view arg)
{
	const std::optional<Expression*> expr = GetExpression(arg.data());

	if (!expr.has_value())
	{
		throw std::runtime_error("Name does not exist");
	}

	auto fn = std::make_shared<UnaryFunction>(op, expr.value());
	m_functions.emplace(std::string(name), std::move(fn));
}

void Calculator::DefineBinaryFunction(std::string_view name, const BinaryOperation& op, std::string_view arg1, std::string_view arg2)
{
	const std::optional<Expression*> expr1 = GetExpression(arg1.data());
	if (!expr1.has_value())
	{
		throw std::runtime_error("Name does not exist");
	}
	const std::optional<Expression*> expr2 = GetExpression(arg2.data());
	if (!expr2.has_value())
	{
		throw std::runtime_error("Name does not exist");
	}

	auto fn = std::make_shared<BinaryFunction>(op, expr1.value(), expr2.value());
	m_functions.emplace(std::string(name), std::move(fn));
}

double Calculator::GetValue(std::string_view name)
{
	return GetExpression(name.data()).value()->GetResult();
}

void Calculator::SetValue(std::string_view name, double value)
{
	std::optional<Expression*> expr = GetExpression(name.data());

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
	const std::optional<Expression*> destination = GetExpression(expressionName.data());
	if (!destination.has_value())
	{
		throw std::runtime_error("Name does not exist");
	}

	SetValue(name, destination.value()->GetResult());
}

std::map<std::string, double> Calculator::ListVariableValues() const
{
	std::map<std::string, double> results;

	for (const auto& [name, fn] : m_variables)
	{
		results.emplace(name, fn.GetResult());
	}

	return results;
}

std::map<std::string, double> Calculator::ListFunctionValues() const
{
	std::map<std::string, double> results;

	for (const auto& [name, fn] : m_functions)
	{
		results.emplace(name, fn->GetResult());
	}

	return results;
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

	return fnIt->second.get();
}
