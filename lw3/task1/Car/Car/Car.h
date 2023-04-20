#pragma once

enum class Direction
{
	Forward,
	Backward,
	NoDirection
};

enum class Gear
{
	Reverse,
	Neutral,
	First,
	Second,
	Third,
	Fourth,
	Fifth
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
	static inline const SpeedRange REVERSE_GEAR_SPEED_RANGE = { -20, 0 };
	static inline const SpeedRange FIRST_GEAR_SPEED_RANGE = { 0, 30 };
	static inline const SpeedRange SECOND_GEAR_SPEED_RANGE = { 20, 50 };
	static inline const SpeedRange THIRD_GEAR_SPEED_RANGE = { 30, 60 };
	static inline const SpeedRange FOURTH_GEAR_SPEED_RANGE = { 40, 90 };
	static inline const SpeedRange FIFTH_GEAR_SPEED_RANGE = { 50, 150 };
	static inline const SpeedRange NEUTRAL_GEAR_SPEED_RANGE = { REVERSE_GEAR_SPEED_RANGE.min, FIFTH_GEAR_SPEED_RANGE.max };

	static bool IsInRange(Gear gear);
	
	bool m_isTurnedOn = false;
	int m_speed = 0;
	Gear m_gear = Gear::Neutral;
};