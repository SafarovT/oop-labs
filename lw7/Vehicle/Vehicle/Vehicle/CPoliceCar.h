#pragma once
#include "IPoliceCar.h"
#include "CCarImpl.h"
#include "CVehicleImpl.h"

class CPoliceCar : public CCarImpl<CVehicleImpl<IPoliceCar, IPoliceMan>>
{
public:
	CPoliceCar(size_t placesCount, MakeOfTheCar makeOfTheCar)
		: CCarImpl(placesCount, makeOfTheCar)
	{
	}
};