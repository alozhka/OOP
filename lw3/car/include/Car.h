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
public:
	Car();

	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(int gear);
	void SetSpeed(int speed);

	bool IsEngineOn() const;
	[[nodiscard]] int GetGear() const;
	[[nodiscard]] int GetSpeed() const;
	[[nodiscard]] std::string GetDirection() const;

private:
	static constexpr int MIN_GEAR = -1;
	static constexpr int MAX_GEAR = 5;
	const std::unordered_map<int, std::pair<int, int>> GEAR_TO_SPEED_RANGES = {
		{ -1, { 0, 20 } },
		{ 0, { 0, 150 } },
		{ 1, { 0, 30 } },
		{ 2, { 20, 50 } },
		{ 3, { 30, 60 } },
		{ 4, { 40, 90 } },
		{ 5, { 50, 150 } }
	};

	bool m_engineOn;
	int m_speed;
	int m_gear;
	Direction m_direction;

	void ThrowIfGearIsInvalid(int gear) const;
	void ThrowIfSpeedIsInvalid(int speed) const;

	void UpdateDirection();
	[[nodiscard]] bool GearInSpeedRange(int gear, int speed) const;
};
