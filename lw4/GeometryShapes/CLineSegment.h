#pragma once
#include "CShape.h"
#include "CPoint.h"

class CLineSegment : public CShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor)
		: CShape(outlineColor, "Line segment")
		, m_startPoint(startPoint)
		, m_endPoint(endPoint)
	{
	}

	CLineSegment(CPoint startPoint, CPoint endPoint)
		: CShape("Line segment")
		, m_startPoint(startPoint)
		, m_endPoint(endPoint)
	{
	}

	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
private:
	CPoint m_startPoint;
	CPoint m_endPoint;
};