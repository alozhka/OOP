#include "../include/CalculatorController.h"

#include <iomanip>
#include <sstream>

class ParseError final : public std::runtime_error
{
public:
	using runtime_error::runtime_error;
};

void PrintMap(std::ostream& out, const std::function<std::map<std::string, double>()>& callback)
{
	std::map<std::string, double> values = callback();

	for (const auto& [name, value] : values)
	{
		out << name << ":" << value << std::endl;
	}
}

namespace Regexes
{
const std::regex VALUE_REGEX(R"regex(\s*([a-zA-Z_][a-zA-Z0-9_.]*)\s*)regex");
const std::regex NAME_VALUE_REGEX(R"regex(\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z0-9_.]*)\s*)regex");
const std::regex EXPRESSION_REGEX(R"regex(\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*([+\-*/])?\s*([a-zA-Z_][a-zA-Z0-9_]*)?)regex");
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
		{ "fn", std::bind_front(&CalculatorController::SetFunction, this) },
		{ "print", std::bind_front(&CalculatorController::PrintExpression, this) },
		{ "let", std::bind_front(&CalculatorController::SetValue, this) },
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

void CalculatorController::AddVariable(const std::string& args) const
{
	const std::smatch matches = ParseRegex(args, Regexes::VALUE_REGEX);

	m_calc.DefineVariable(matches[1].str());
}

void CalculatorController::SetValue(const std::string& args) const
{
	const std::smatch matches = ParseRegex(args, Regexes::NAME_VALUE_REGEX);

	const std::string name = matches[1].str();
	const std::string arg1 = matches[2].str();

	if (arg1.empty())
	{
		throw std::runtime_error("Invalid usage");
	}
	if (!IsNumericString(arg1))
	{
		m_calc.SetValue(name, arg1);
	}
	else
	{
		m_calc.SetValue(name, std::stod(arg1));
	}
}

void CalculatorController::SetFunction(const std::string& args)
{
	const std::smatch matches = ParseRegex(args, Regexes::EXPRESSION_REGEX);

	const std::string name = matches[1].str();
	const std::string arg1 = matches[2].str();
	const std::string operation = matches[3].str();
	const std::string arg2 = matches[4].str();

	if (operation.empty() && arg2.empty())
	{
		m_calc.DefineUnaryFunction(name, Operations::Unary::IDENTITY, arg1);
		return;
	}

	const auto operationIt = m_operations.find(operation);
	if (arg2.empty() || operationIt == m_operations.end())
	{
		throw std::runtime_error("Invalid usage");
	}

	m_calc.DefineBinaryFunction(name, operationIt->second, arg1, arg2);
}

void CalculatorController::PrintExpression(const std::string& args) const
{
	const std::smatch matches = ParseRegex(args, Regexes::VALUE_REGEX);

	const double result = m_calc.GetValue(matches[1].str());
	m_output << result << std::endl;
}

void CalculatorController::PrintFunctions() const
{
	PrintMap(m_output, std::bind_front(&Calculator::ListFunctionValues, m_calc));
}

void CalculatorController::PrintVariables() const
{
	PrintMap(m_output, std::bind_front(&Calculator::ListVariableValues, m_calc));
}

std::smatch CalculatorController::ParseRegex(const std::string& str, const std::regex& regex)
{
	std::smatch match;
	if (!std::regex_match(str, match, regex))
	{
		throw ParseError("Invalid usage");
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
			std::string args;
			std::getline(ss, args);
			it->second(args);
		}
		catch (const std::exception& e)
		{
			m_output << e.what() << std::endl;
		}
	}
}