#include "../include/Car.h"

std::string Car::GetDirection() const
{
	switch (m_direction)
	{
	case Direction::Backward:
		return "backward";
	case Direction::Forward:
		return "forward";
	case Direction::StandingStill:
		return "standing still";
	default:
		throw std::runtime_error("Invalid direction");
	}
}

Car::Car()
	: m_engineOn(false)
	, m_speed(0)
	, m_gear(0)
	, m_direction(Direction::StandingStill)
{
}

void Car::PrintInfo(std::ostream& out) const
{
	out << std::format(
		"Engine: {0}\nDirection: {1}\nSpeed: {2}\nGear: {3}\n",
		m_engineOn ? "on" : "off",
		GetDirection(),
		m_speed,
		m_gear);
}
