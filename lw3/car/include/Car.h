#pragma once
#include <ostream>

enum class Direction
{
	Backward,
	StandingStill,
	Forward,
};

class Car
{
	bool m_engineOn;
	int m_speed;
	int m_gear;
	Direction m_direction;

	[[nodiscard]] std::string GetDirection() const;

public:
	explicit Car();
	void PrintInfo(std::ostream& out) const;
};
