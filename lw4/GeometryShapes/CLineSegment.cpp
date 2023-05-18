#include "CLineSegment.h"
#include <math.h>

double CLineSegment::GetPerimeter() const
{
	double differenceInX = pow(m_startPoint.x - m_endPoint.x, 2);
	double differenceInY = pow(m_startPoint.y - m_endPoint.y, 2);
	return sqrt(differenceInX + differenceInY) ;
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