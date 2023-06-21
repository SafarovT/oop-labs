#pragma once
#include "ITaxi.h"
#include "CCarImpl.h"
#include "CVehicleImpl.h"

class CTaxi : public CCarImpl<CVehicleImpl<ITaxi, IPerson>>
{
public:
	CTaxi(size_t placesCount, MakeOfTheCar makeOfTheCar)
		: CCarImpl(placesCount, makeOfTheCar)
	{
	}
};