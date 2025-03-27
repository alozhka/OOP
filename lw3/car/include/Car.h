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
	static constexpr int m_MIN_GEAR = -1;
	static constexpr int m_MAX_GEAR = 5;

	bool m_engineOn;
	int m_speed;
	int m_gear;
	Direction m_direction;

	std::string GetDirection() const;
	void UpdateDirection();
	static bool GearInSpeedRange(int gear, int speed);

public:
	explicit Car();

	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(int gear);
	void SetSpeed(int speed);

	void PrintInfo(std::ostream& out) const;
};
