#pragma once
#include "BinaryOperation.h"
#include "Function.h"
#include "UnaryOperation.h"
#include "Variable.h"
#include <map>
#include <memory>
#include <optional>

class Calculator
{
public:
	Calculator();

	void DefineVariable(std::string_view name, double value = NAN);
	void DefineUnaryFunction(std::string_view name, const UnaryOperation& op, std::string_view arg);
	void DefineBinaryFunction(std::string_view name, const BinaryOperation& op, std::string_view arg1, std::string_view arg2);

	double GetValue(std::string_view name);
	void SetValue(std::string_view name, double value);
	void SetValue(std::string_view name, std::string_view expressionName);
	std::map<std::string, double> ListVariableValues() const;
	std::map<std::string, double> ListFunctionValues() const;

private:
	std::optional<Expression*> GetExpression(std::string_view name);
	void ThrowIfNameIsTaken(std::string_view name) const;

	std::map<std::string, Variable> m_variables;
	std::map<std::string, std::shared_ptr<Function>> m_functions;
};