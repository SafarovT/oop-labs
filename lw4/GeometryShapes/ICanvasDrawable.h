#pragma once
#include "ICanvas.h"

class ICanvasDrawable 
{
// виртуальный дестркутор, либо защищенный (чеклист по сдаче лаб)
public:
	virtual ~ICanvasDrawable() {};
	virtual void Draw(ICanvas& canvas) const = 0;
};