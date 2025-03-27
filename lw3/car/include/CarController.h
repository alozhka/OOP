#pragma once
#include "Car.h"
#include <istream>

class CarController
{
public:
	CarController(Car& car, std::istream& input, std::ostream& output);
	bool HandleCommand() const;

private:
	void Info() const;
	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(std::istream& args);
	void SetSpeed(std::istream& args);

	using Command = std::function<void(std::istream& args)>;
	using ActionMap = std::unordered_map<std::string, Command>;
	const ActionMap m_actionMap;

	std::istream& m_input;
	std::ostream& m_output;
	Car m_car;
};
