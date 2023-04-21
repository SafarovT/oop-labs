#pragma once
#include <optional>

// todo: validate speed to be >= 0
// todo: выдавать более понятне соощение об ошибке

// enum class
enum class Direction
{
	Backward = -1,
	NoDirection = 0,
	Forward = 1
};

// enum class
enum class Gear
{
	Reverse = -1,
	Neutral = 0,
	First = 1,
	Second = 2,
	Third = 3,
	Fourth = 4,
	Fifth = 5
};

class Car
{
public:
	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	Gear GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(Gear gear);
	bool SetSpeed(int speed);

private:
	struct SpeedRange
	{
		int min;
		int max;
	};
	static inline const SpeedRange REVERSE_GEAR_SPEED_RANGE = { 0, 20 };
	static inline const SpeedRange FIRST_GEAR_SPEED_RANGE = { 0, 30 };
	static inline const SpeedRange SECOND_GEAR_SPEED_RANGE = { 20, 50 };
	static inline const SpeedRange THIRD_GEAR_SPEED_RANGE = { 30, 60 };
	static inline const SpeedRange FOURTH_GEAR_SPEED_RANGE = { 40, 90 };
	static inline const SpeedRange FIFTH_GEAR_SPEED_RANGE = { 50, 150 };
	static inline const SpeedRange NEUTRAL_GEAR_SPEED_RANGE = { 0, FIFTH_GEAR_SPEED_RANGE.max };

	static bool IsSpeedInRange(int speed, SpeedRange range);
	static std::optional<SpeedRange> GetSpeedRangeForGear(Gear gear);
	bool IsDirectionAllowsToSetGear(Gear gear);
	
	bool m_isTurnedOn = false;
	int m_speed = 0;
	Gear m_gear = Gear::Neutral;
};