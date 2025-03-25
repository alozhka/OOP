#include "../include/CarController.h"
#include <ostream>
#include <sstream>

CarController::CarController(Car& car, std::istream& input, std::ostream& output)
	: m_actionMap({ { "Info", [this](std::istream&) { return Info(); }} })
	, m_input(input)
	, m_output(output)
	, m_car(car)
{
}

bool CarController::HandleCommand() const
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream ss(commandLine);

	std::string action;
	ss >> action;

	const auto it = m_actionMap.find(action);
	if (it == m_actionMap.end())
	{
		return false;
	}

	return it->second(ss);
}

bool CarController::Info() const
{
	m_car.PrintInfo(m_output);
	return true;
}
