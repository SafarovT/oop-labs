#include "CCircle.h"
#include "common.h"
#define _USE_MATH_DEFINES
#include <math.h>

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
	std::string circleInfo = CSolidShape::ToString();
	circleInfo += " Center: " + m_center.ToString() + " Radius: " + DoubleToString(GetRadius());
	return circleInfo;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}