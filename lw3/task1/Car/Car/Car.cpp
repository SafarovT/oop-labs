#include "Car.h"

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
	return m_speed;
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

bool Car::SetSpeed(int speed)
{
	Car::SpeedRange 
}

bool Car::SetGear(Gear gear)
{

}

Car::SpeedRange GetGearSpeedRange(Gear gear)
{

}