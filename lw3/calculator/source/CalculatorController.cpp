#include "../include/CalculatorController.h"

#include <iomanip>
#include <sstream>

namespace Regexes
{
const std::regex VALUE_REGEX(R"regex(\s*([a-zA-Z_][a-zA-Z0-9_.]*)\s*)regex");
const std::regex NAME_VALUE_REGEX(R"regex(\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z0-9_.]*)\s*)regex");
const std::regex EXPRESSION_REGEX(R"regex(\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*([+\-*/=])?\s*([a-zA-Z_][a-zA-Z0-9_]*)?)regex");
} // namespace Regexes

bool IsNumericString(const std::string& s)
{
	for (const char c : s)
	{
		if (!std::isdigit(c) && c != '.' && c != '-')
		{
			return false;
		}
	}
	return true;
}

CalculatorController::CalculatorController(Calculator& calc, std::istream& input, std::ostream& output)
	: m_commands{
		{ "var", std::bind_front(&CalculatorController::AddVariable, this) },
		{ "fn", std::bind_front(&CalculatorController::AddFunction, this) },
		{ "print", std::bind_front(&CalculatorController::PrintExpression, this) },
		{ "let", std::bind_front(&CalculatorController::UpdateOrCreateExpression, this) },
		{ "printvars", [this](const std::string&) { return this->PrintVariables(); } },
		{ "printfns", [this](const std::string&) { return this->PrintFunctions(); } }
	}
	, m_operations{ { "+", Operations::SUM }, { "-", Operations::SUBTRACT }, { "*", Operations::MULTIPLY }, { "/", Operations::DIVIDE } }
	, m_calc(calc)
	, m_input(input)
	, m_output(output)
{
	m_output << std::fixed << std::setprecision(2);
}

void CalculatorController::AddVariable(const std::string& args)
{
	const std::smatch matches = ParseRegex(args, Regexes::VALUE_REGEX);

	m_calc.DefineVariable(matches[1].str());
}

void CalculatorController::UpdateOrCreateExpression(const std::string& args)
{
	try
	{
		const std::smatch matches = ParseRegex(args, Regexes::NAME_VALUE_REGEX);

		const std::string name = matches[1].str();
		const std::string arg1 = matches[2].str();

		if (!IsNumericString(arg1))
		{
			m_calc.UpdateOrCreateVariable(name, arg1);
		}
		else
		{
			m_calc.UpdateOrCreateVariable(name, std::stod(arg1));
		}
		return;
	}
	catch (std::runtime_error&)
	{
	}

	const std::smatch matches = ParseRegex(args, Regexes::EXPRESSION_REGEX);

	const std::string name = matches[1].str();
	const std::string arg1 = matches[2].str();
	const std::string operation = matches[3].str();
	const std::string arg2 = matches[4].str();

	if (operation.empty() && arg2.empty())
	{
		m_calc.UpdateOrCreateVariable(name, std::stod(arg1));
	}

	const auto operationIt = m_operations.find(operation);
	if (operationIt == m_operations.end())
	{
		throw std::invalid_argument("Invalid usage");
	}

	m_calc.DefineFunction(name, operationIt->second, arg1, arg2);
}

void CalculatorController::AddFunction(const std::string& args)
{
	const std::smatch matches = ParseRegex(args, Regexes::EXPRESSION_REGEX);

	const std::string name = matches[1].str();
	const std::string arg1 = matches[2].str();
	const std::string operation = matches[3].str();
	const std::string arg2 = matches[4].str();

	const auto operationIt = m_operations.find(operation);
	if (operationIt == m_operations.end())
	{
		throw std::invalid_argument("Invalid usage");
	}

	m_calc.DefineFunction(name, operationIt->second, arg1, arg2);
}

void CalculatorController::PrintExpression(const std::string& args)
{
	const std::smatch matches = ParseRegex(args, Regexes::VALUE_REGEX);

	const double result = m_calc.GetValue(matches[1].str());
	m_output << result << std::endl;
}

void CalculatorController::PrintFunctions()
{
	std::map<std::string, double> values = m_calc.ListFunctionValues();

	for (const auto& [name, value] : values)
	{
		m_output << name << ":" << value << std::endl;
	}
}

void CalculatorController::PrintVariables()
{
	std::map<std::string, double> values = m_calc.ListVariableValues();

	for (const auto& [name, value] : values)
	{
		m_output << name << ":" << value << std::endl;
	}
}

std::smatch CalculatorController::ParseRegex(const std::string& str, const std::regex& regex)
{
	std::smatch match;
	if (!std::regex_match(str, match, regex))
	{
		throw std::runtime_error("Invalid usage");
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
			m_output << "Unknown command\n";
			continue;
		}

		try
		{
			std::string command;
			std::getline(ss, command);
			it->second(command);
		}
		catch (const std::runtime_error& e)
		{
			m_output << e.what() << std::endl;
		}
	}
}