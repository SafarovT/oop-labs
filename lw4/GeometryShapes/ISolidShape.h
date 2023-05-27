#pragma once
#include "IShape.h"

class ISolidShape : virtual public IShape
{
public:
	virtual ~ISolidShape() {};
	virtual uint32_t GetFillColor() const = 0;
};