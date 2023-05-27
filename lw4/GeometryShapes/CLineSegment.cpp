#include "CLineSegment.h"
#include <math.h>

double CLineSegment::GetPerimeter() const
{
	double differenceInX = m_startPoint.x - m_endPoint.x;
	double differenceInY = m_startPoint.y - m_endPoint.y;
	return sqrt(differenceInX * differenceInX + differenceInY * differenceInY);
}

std::string CLineSegment::ToString() const
{
	std::string lineInfo = CShape::ToString();
	lineInfo += " Start point: " + m_startPoint.ToString() + " End point: " + m_endPoint.ToString();

	return lineInfo;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void CLineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_startPoint, m_endPoint, GetOutlineColor());
}