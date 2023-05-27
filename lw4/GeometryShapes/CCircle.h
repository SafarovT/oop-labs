#pragma once
#include "CSolidShape.h"
#include "CPoint.h"

class CCircle : public CSolidShape
{
public:
	CCircle(
		CPoint center,
		double radius,
		uint32_t outlineColor,
		uint32_t fillColor
	)
		: CSolidShape(outlineColor, fillColor, "Circle")
		, m_center(center)
	{
		if (radius < 0)
		{
			radius = 0;
		}
		m_radius = radius;
	}

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetCenter() const;
	double GetRadius() const;
	void Draw(ICanvas& canvas) const override;
private:
	CPoint m_center;
	double m_radius;
};