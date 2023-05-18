#pragma once
#include "CSolidShape.h"
#include "CPoint.h"

class CTriangle : public CSolidShape
{
public:
	CTriangle(
		CPoint vertex1,
		CPoint vertex2,
		CPoint vertex3,
		uint32_t outlineColor,
		uint32_t fillColor
	)
		: CSolidShape	(outlineColor, fillColor, "Triangle")
		, m_vertex1(vertex1)
		, m_vertex2(vertex2)
		, m_vertex3(vertex3)
	{
	}

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
};