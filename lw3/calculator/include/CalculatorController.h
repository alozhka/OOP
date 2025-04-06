#pragma once
#include "Calculator.h"
#include <regex>
#include <functional>
#include <istream>

class CalculatorController
{
public:
	CalculatorController(Calculator& calc, std::istream& input, std::ostream& output);
	void HandleInput();

private:
	void AddVariable(std::istream& args);
	void AddFunction(std::istream& args);
	void SetValue(std::istream& args);
	void PrintExpression(std::istream& args);

	static std::smatch ParseRegex(std::istream& args, const std::regex& regex);

	using Command = std::function<void(std::istream&)>;

	std::unordered_map<std::string, Command> m_commands;
	std::unordered_map<std::string, Operation> m_operations;
	Calculator m_calc;
	std::istream& m_input;
	std::ostream& m_output;
};
