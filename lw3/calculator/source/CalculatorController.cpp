#include "../include/CalculatorController.h"

#include <iostream>
#include <sstream>

namespace Regexes
{
const std::regex VALUE_REGEX(R"(^\s*([a-zA-Z_][a-zA-Z0-9_]*)$)");
const std::regex NAME_VALUE_REGEX(R"(^\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z_][a-zA-Z0-9_]*)(\+|\-|\*|\/)?([a-zA-Z_][a-zA-Z0-9_]*)?$)");
}


CalculatorController::CalculatorController(Calculator& calc, std::istream& input, std::ostream& output)
	: m_commands{
		{ "var", std::bind_front(&CalculatorController::AddVariable, this) },
		{ "fn", std::bind_front(&CalculatorController::AddFunction, this) },
		{ "print", std::bind_front(&CalculatorController::PrintExpression, this) },
		{ "let", std::bind_front(&CalculatorController::SetValue, this) }
	}
	, m_operations{ { "+", Operations::SUM }, { "-", Operations::SUBTRACT }, { "*", Operations::MULTIPLY }, { "/", Operations::DIVIDE } }
	, m_calc(calc)
	, m_input(input)
	, m_output(output)
{
}

void CalculatorController::AddVariable(std::istream& args)
{
	const std::smatch matches = ParseRegex(args, Regexes::VALUE_REGEX);

	m_calc.DefineVariable(matches[1].str());
}

void CalculatorController::SetValue(std::istream& args)
{
	const std::smatch matches = ParseRegex(args, Regexes::NAME_VALUE_REGEX);

	const std::string name = matches[1].str();
	const double value = std::stod(matches[2].str());

	m_calc.SetValue(name, value);
}

void CalculatorController::AddFunction(std::istream& args)
{
	std::smatch matches = ParseRegex(args, Regexes::NAME_VALUE_REGEX);

	std::string name = matches[1].str();
	std::string arg1 = matches[2].str();
	std::string operation = matches[3].str();
	std::string arg2 = matches[4].str();

	auto it = m_operations.find(operation);
	if (it == m_operations.end())
	{
		throw std::invalid_argument("Invalid usage");
	}

	m_calc.DefineFunction(name, it->second, arg1, arg2);
}

void CalculatorController::PrintExpression(std::istream& args)
{
	const std::smatch matches = ParseRegex(args, Regexes::VALUE_REGEX);

	const double result = m_calc.GetValue(matches[1].str());
	std::cout << result << std::endl;
}

std::smatch CalculatorController::ParseRegex(std::istream& args, const std::regex& regex)
{
	std::string str;
	std::getline(args, str);
	std::smatch match;
	if (!std::regex_match(str, match, regex))
	{
		throw std::invalid_argument("Invalid usage");
	}
	return match;
}

void CalculatorController::HandleInput()
{
	std::string commandLine;
	while (std::getline(m_input, commandLine))
	{
		std::istringstream ss(commandLine);

		std::string action;
		ss >> action;

		const auto it = m_commands.find(action);
		if (it == m_commands.end())
		{
			m_output << "Unknown command";
			continue;
		}

		try
		{
			it->second(ss);
		}
		catch (const std::runtime_error& e)
		{
			m_output << e.what() << std::endl;
		}
	}
}