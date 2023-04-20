#include "Car.h"
#include <math.h>

bool Car::IsTurnedOn() const
{
	return m_isTurnedOn;
}

Direction Car::GetDirection() const
{
	if (m_speed > 0)
	{
		return Direction::Forward;
	}
	else if (m_speed < 0)
	{
		return Direction::Backward;
	}

	return Direction::NoDirection;
}

int Car::GetSpeed() const
{
	return abs(m_speed);
}

Gear Car::GetGear() const
{
	return m_gear;
}

bool Car::TurnOnEngine()
{
	m_isTurnedOn = true;

	return true;
}

bool Car::TurnOffEngine()
{
	if (m_gear == Gear::Neutral && m_speed == 0)
	{
		m_isTurnedOn = false;
		return true;
	}

	return false;
}

std::optional<Car::SpeedRange> Car::GetSpeedRangeForGear(Gear gear)
{
	switch (gear)
	{
	case Gear::Reverse:
		return REVERSE_GEAR_SPEED_RANGE;
	case Gear::Neutral:
		return NEUTRAL_GEAR_SPEED_RANGE;
	case Gear::First:
		return FIRST_GEAR_SPEED_RANGE;
	case Gear::Second:
		return SECOND_GEAR_SPEED_RANGE;
	case Gear::Third:
		return THIRD_GEAR_SPEED_RANGE;
	case Gear::Fourth:
		return FOURTH_GEAR_SPEED_RANGE;
	case Gear::Fifth:
		return FIFTH_GEAR_SPEED_RANGE;
	default:
		return std::nullopt;
	}
}

bool Car::IsSpeedInRange(int speed, SpeedRange range)
{
	return (speed >= range.min) && (speed <= range.max);
}

bool Car::SetSpeed(int speed)
{
	if (speed == abs(m_speed))
	{
		return true;
	}
	auto avaiableSpeedRange = GetSpeedRangeForGear(m_gear);
	if (!avaiableSpeedRange || !IsSpeedInRange(speed, *avaiableSpeedRange) || !m_isTurnedOn)
	{
		return false;
	}
	if (m_gear == Gear::Neutral && speed > abs(m_speed))
	{
		return false;
	}
	if (GetDirection() == Direction::Backward || m_gear == Gear::Reverse)
	{
		speed *= -1;
	}
	m_speed = speed;

	return true;
}

bool Car::IsDirectionAllowsToSetGear(Gear gear)
{
	Direction carDirection = GetDirection();
	if (gear == Gear::Reverse)
	{
		return carDirection == Direction::NoDirection;
	}
	if (gear > Gear::First)
	{
		return carDirection != Direction::Backward;
	}

	return true;
}

bool Car::SetGear(Gear gear)
{
	if (gear == m_gear)
	{
		return true;
	}
	auto avaiableSpeedRange = GetSpeedRangeForGear(gear);
	if (!avaiableSpeedRange || !IsSpeedInRange(m_speed, *avaiableSpeedRange) || !m_isTurnedOn)
	{
		return false;
	}
	if (!IsDirectionAllowsToSetGear(gear))
	{
		return false;
	}
	m_gear = gear;

	return true;
}