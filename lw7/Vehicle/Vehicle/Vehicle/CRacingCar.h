#pragma once
#include "IRacingCar.h"
#include "CVehicleImpl.h"
#include "CCarImpl.h"

class CRacingCar : public CCarImpl<CVehicleImpl<IRacingCar, IRacer>>
{
public:
	CRacingCar(size_t placesCount, MakeOfTheCar makeOfTheCar)
		: CCarImpl(placesCount, makeOfTheCar)
	{
	}
};