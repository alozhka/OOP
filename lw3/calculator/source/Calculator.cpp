#include "../include/Calculator.h"
#include "../include/BinaryFunction.h"
#include "../include/UnaryFunction.h"

#include <stdexcept>

Calculator::Calculator() = default;

void Calculator::DefineVariable(std::string_view name, double value)
{
	ThrowIfNameIsTaken(name);

	auto var = std::make_shared<Variable>(value);
	m_variables.emplace(std::string(name), std::move(var));
}

void Calculator::DefineUnaryFunction(std::string_view name, const UnaryOperation& op, std::string_view arg)
{
	ThrowIfNameIsTaken(name);

	const std::shared_ptr<Expression> expr = GetExpression(arg);

	if (expr == nullptr)
	{
		throw std::runtime_error("Name does not exist");
	}

	auto fn = std::make_shared<UnaryFunction>(op, expr);
	m_functions.emplace(std::string(name), std::move(fn));
}

void Calculator::DefineBinaryFunction(std::string_view name, const BinaryOperation& op, std::string_view arg1, std::string_view arg2)
{
	ThrowIfNameIsTaken(name);

	const std::shared_ptr<Expression> expr1 = GetExpression(arg1);
	if (expr1 == nullptr)
	{
		throw std::runtime_error("Name does not exist");
	}
	const std::shared_ptr<Expression> expr2 = GetExpression(arg2);
	if (expr2 == nullptr)
	{
		throw std::runtime_error("Name does not exist");
	}

	auto fn = std::make_shared<BinaryFunction>(op, expr1, expr2);
	m_functions.emplace(std::string(name), std::move(fn));
}

double Calculator::GetValue(std::string_view name)
{
	std::shared_ptr<Expression> expr = GetExpression(name);
	if (expr == nullptr)
	{
		throw std::runtime_error("Name does not exist");
	}

	return expr->GetResult();
}

void Calculator::SetValue(std::string_view name, double value)
{
	std::shared_ptr<Expression> expr = GetExpression(name.data());

	if (expr == nullptr)
	{
		auto var = std::make_shared<Variable>(value);
		m_variables.emplace(std::string(name), std::move(var));
	}
	else
	{
		auto* var = dynamic_cast<Variable*>(expr.get());
		if (var == nullptr)
		{
			throw std::runtime_error("Cannot set value to function");
		}
		var->SetValue(value);
	}
}

void Calculator::SetValue(std::string_view name, std::string_view expressionName)
{
	const std::shared_ptr<Expression> destination = GetExpression(expressionName.data());
	if (destination == nullptr)
	{
		throw std::runtime_error("Name does not exist");
	}

	SetValue(name, destination->GetResult());
}

std::map<std::string, double> Calculator::ListVariableValues() const
{
	std::map<std::string, double> results;

	for (const auto& [name, var] : m_variables)
	{
		results.emplace(name, var->GetResult());
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

std::shared_ptr<Expression> Calculator::GetExpression(std::string_view name)
{
	if (const auto varIt = m_variables.find(name.data()); varIt != m_variables.end())
	{
		return varIt->second;
	}

	const auto fnIt = m_functions.find(name.data());
	if (fnIt == m_functions.end())
	{
		return nullptr;
	}

	return fnIt->second;
}

void Calculator::ThrowIfNameIsTaken(std::string_view name) const
{
	if (m_variables.contains(name.data()) || m_functions.contains(name.data()))
	{
		throw std::runtime_error("Name already exists");
	}
}
