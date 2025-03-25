#pragma once
#include "Car.h"

class CarController
{
public:
	CarController(Car& car, std::istream& input, std::ostream& output);
	bool HandleCommand() const;

private:
	bool Info() const;
	bool TurnOnEngine() const;
	bool TurnOffEngine() const;
	bool SetGear(std::istream& args);
	bool SetSpeed(std::istream& args);

	using Command = std::function<bool(std::istream& args)>;
	using ActionMap = std::unordered_map<std::string, Command>;
	const ActionMap m_actionMap;

	std::istream& m_input;
	std::ostream& m_output;
	Car m_car;
};
