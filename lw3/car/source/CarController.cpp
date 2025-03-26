#include "../include/CarController.h"
#include <ostream>
#include <sstream>

CarController::CarController(Car& car, std::istream& input, std::ostream& output)
	: m_actionMap({
		  { "Info", [this](std::istream&) { return Info(); } },
		  { "SetGear", std::bind_front(&CarController::SetGear, this) },
		  { "SetSpeed", std::bind_front(&CarController::SetSpeed, this) },
		  { "EngineOn", [this](std::istream&) { return TurnOnEngine(); } },
		  { "EngineOff", [this](std::istream&) { return TurnOffEngine(); } },
	  })
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

	try
	{
		it->second(ss);
	}
	catch (const std::runtime_error& e)
	{
		m_output << e.what() << std::endl;
	}

	return true;
}

bool CarController::TurnOnEngine()
{
	return m_car.TurnOnEngine();
}

bool CarController::TurnOffEngine()
{
	return m_car.TurnOffEngine();
}

int ReadInteger(std::istream& in)
{
	int i;
	if (!(in >> i))
	{
		throw std::invalid_argument("Invalid command argument");
	}

	return i;
}

bool CarController::SetGear(std::istream& args)
{
	const int gear = ReadInteger(args);
	return m_car.SetGear(gear);
}

bool CarController::SetSpeed(std::istream& args)
{
	const int speed = ReadInteger(args);
	return m_car.SetSpeed(speed);
}

bool CarController::Info() const
{
	m_car.PrintInfo(m_output);
	return true;
}
