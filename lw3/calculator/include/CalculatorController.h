#pragma once
#include "Calculator.h"
#include <functional>
#include <regex>

class CalculatorController
{
public:
	CalculatorController(Calculator& calc, std::istream& input, std::ostream& output);
	void HandleInput();

private:
	void AddVariable(const std::string& args);
	void SetFunction(const std::string& args);

	void SetValue(const std::string& args);

	void PrintExpression(const std::string& args);
	void PrintVariables() const;
	void PrintFunctions() const;

	static std::smatch ParseRegex(const std::string& str, const std::regex& regex);

	using Command = std::function<void(const std::string&)>;

	std::unordered_map<std::string, Command> m_commands;
	std::unordered_map<std::string, BinaryOperation> m_operations;
	Calculator m_calc;
	std::istream& m_input;
	std::ostream& m_output;
};
