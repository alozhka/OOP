#include "../include/Car.h"

#include <map>

Car::Car()
	: m_engineOn(false)
	, m_speed(0)
	, m_gear(0)
	, m_direction(Direction::StandingStill)
{
}

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
		throw std::invalid_argument("Invalid direction");
	}
}

void Car::TurnOnEngine()
{
	if (!m_engineOn)
	{
		m_engineOn = true;
		m_direction = Direction::StandingStill;
		m_gear = 0;
		m_speed = 0;
	}
}

void Car::TurnOffEngine()
{
	if (m_speed != 0 || m_gear != 0)
	{
		throw std::runtime_error("Сar must be stopped and in neutral gear");
	}

	m_engineOn = false;
}

void Car::SetGear(int gear)
{
	if (gear < m_MIN_GEAR || gear > m_MAX_GEAR)
	{
		throw std::runtime_error("Invalid gear");
	}

	if (!m_engineOn && gear != 0)
	{
		throw std::runtime_error("Gear is settable when engine is turned on");
	}

	if (m_gear == 0 && gear > 0 && m_direction == Direction::Backward)
	{
		throw std::runtime_error("Unsuitable current gear");
	}

	if (m_gear < 0 && gear > 0)
	{
		throw std::runtime_error("Unsuitable current gear");
	}

	if (gear != 0 && !GearInSpeedRange(gear, m_speed))
	{
		throw std::runtime_error("Unsuitable current gear");
	}

	m_gear = gear;
}

void Car::SetSpeed(int speed)
{
	if (speed < 0)
	{
		throw std::runtime_error("Speed must be positive number");
	}

	if (!m_engineOn)
	{
		throw std::runtime_error("Speed is settable when engine is turned on");
	}

	if (m_gear == 0 && speed > m_speed)
	{
		throw std::runtime_error("Unsuitable current speed");
	}

	if (m_gear != 0 && !GearInSpeedRange(m_gear, speed))
	{
		throw std::runtime_error("Unsuitable current speed");
	}

	m_speed = speed;
	UpdateDirection();
}

void Car::PrintInfo(std::ostream& out) const
{
	out << "Engine: " << (m_engineOn ? "on" : "off") << std::endl;
	out << "Direction: " << GetDirection() << std::endl;
	out << "Speed: " << m_speed << std::endl;
	out << "Gear: " << m_gear << std::endl;
}

bool Car::GearInSpeedRange(int gear, int speed)
{
	static const std::unordered_map<int, std::pair<int, int>> GEAR_TO_SPEED_RANGES = {
		{ -1, { 0, 20 } },
		{ 0, { 0, 150 } },
		{ 1, { 0, 30 } },
		{ 2, { 20, 50 } },
		{ 3, { 30, 60 } },
		{ 4, { 40, 90 } },
		{ 5, { 50, 150 } }
	};

	const auto [leftBorder, rightBorder] = GEAR_TO_SPEED_RANGES.at(gear);
	return leftBorder <= speed && speed <= rightBorder;
}

void Car::UpdateDirection()
{
	if (m_gear < 0 && m_speed != 0)
	{
		m_direction = Direction::Backward;
	}
	if (m_gear == 0)
	{
		m_direction = Direction::StandingStill;
	}
	if (m_gear > 0)
	{
		m_direction = Direction::Forward;
	}
}
