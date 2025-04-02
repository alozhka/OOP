#include "../include/CalculatorController.h"
#include <sstream>

CalculatorController::CalculatorController(Calculator& calc, std::istream& input, std::ostream& output)
	: m_calc(calc)
	, m_input(input)
	, m_output(output)
	, m_operations{
		{ "+", Operations::SUM },
		{ "-", Operations::SUBTRACT },
		{ "*", Operations::MULTIPLY },
		{ "/", Operations::DIVIDE }
	}
	, m_commands{ { "var", std::bind_front(&CalculatorController::AddVariable, this) }, { "fn", std::bind_front(&CalculatorController::AddFunction, this) } }
{
}

void CalculatorController::AddVariable(std::istream& args)
{
	std::string str;
	std::getline(args, str);
	std::smatch matches = ParseRegex(
		R"(^\s+([a-zA-Z_][a-zA-Z0-9_]*)$)",
		str);

	m_calc.DefineVariable(matches[0].str());
}

void CalculatorController::AddFunction(std::istream& args)
{
	std::string str;
	std::getline(args, str);
	std::smatch matches = ParseRegex(
		R"(^\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z_][a-zA-Z0-9_]*)(\+|\-|\*|\/)?([a-zA-Z_][a-zA-Z0-9_]*)?$)",
		str);

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
std::smatch CalculatorController::ParseRegex(const std::string& pattern, const std::string& str)
{
	std::regex regex(pattern);
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