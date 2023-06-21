#pragma once
#include "ICar.h"

template <class Base>
class CCarImpl : public Base
{
public:
	CCarImpl(size_t placesCount, MakeOfTheCar makeOfTheCar)
		: Base(placesCount)
		, m_makeOfTheCar(makeOfTheCar)
	{
	}

	MakeOfTheCar GetMakeOfTheCar() const
	{
		return m_makeOfTheCar;
	}

private:
	MakeOfTheCar m_makeOfTheCar;
};