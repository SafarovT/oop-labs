#pragma once
#include "CSolidShape.h"
#include "CPoint.h"

class CRectangle : public CSolidShape
{
public:
	CRectangle(
		CPoint leftTop,
		CPoint rightBottom,
		uint32_t outlineColor,
		uint32_t fillColor
	)
		: CSolidShape(outlineColor, fillColor, "Rectangle")
		, m_leftTop(leftTop)
		, m_rightBottom(rightBottom)
	{
	}

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
	void Draw(ICanvas& canvas) const override;
private:
	CPoint m_leftTop;
	CPoint m_rightBottom;
};