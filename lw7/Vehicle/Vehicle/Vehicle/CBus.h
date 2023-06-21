#pragma once
#include "IBus.h"
#include "CVehicleImpl.h"

class CBus : public CVehicleImpl<IBus, IPerson>
{
public:
	CBus(size_t placesCount)
		: CVehicleImpl(placesCount)
	{}
};