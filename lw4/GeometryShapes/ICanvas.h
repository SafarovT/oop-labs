#pragma once
#include "CPoint.h"
#include <vector>

class ICanvas
{
public:
	virtual ~ICanvas() {};
	virtual void DrawLine(CPoint from, CPoint to, uint32_t lineColor) = 0;
	virtual void FillPolygon(std::vector<CPoint> points, uint32_t fillColor, uint32_t outlineColor) = 0;
	virtual void FillCircle(CPoint center, double radius, uint32_t FillCircle, uint32_t outlineColor) = 0;
};