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

	[[nodiscard]] std::string GetDirection() const;
	static bool GearInSpeedRange(int gear, int speed);

public:
	explicit Car();

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	void UpdateDirection();

	void PrintInfo(std::ostream& out) const;
};
