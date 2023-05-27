#include "CTriangle.h"
#include <math.h>
#include "CLineSegment.h"

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

double CTriangle::GetArea() const
{
	return abs((m_vertex2.x - m_vertex1.x) * (m_vertex3.y - m_vertex1.y) - (m_vertex3.x - m_vertex1.x) * (m_vertex2.y - m_vertex1.y)) / 2;
}

double CTriangle::GetPerimeter() const
{
	CLineSegment edge1(m_vertex1, m_vertex2);
	CLineSegment edge2(m_vertex2, m_vertex3);
	CLineSegment edge3(m_vertex3, m_vertex1);

	return edge1.GetPerimeter() + edge2.GetPerimeter() + edge3.GetPerimeter();
}


std::string CTriangle::ToString() const
{
	std::string triangleInfo = CSolidShape::ToString();
	triangleInfo += " Vertexes: " + m_vertex1.ToString() + ", " + m_vertex2.ToString() + ", " + m_vertex3.ToString();

	return triangleInfo;
}

void CTriangle::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> vertexes = {
		GetVertex1(),
		GetVertex2(),
		GetVertex3()
	};

	canvas.FillPolygon(vertexes, GetFillColor(), GetOutlineColor());
}