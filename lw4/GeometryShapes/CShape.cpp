#include "CShape.h"
#include "common.h"

double CShape::GetArea() const
{
	return 0;
}

double CShape::GetPerimeter() const
{
	return 0;
}

uint32_t CShape::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CShape::ToString() const
{
	std::string shapeDescription;
	shapeDescription = m_shapeName + ": "
		+ " area: " + DoubleToString(GetArea())
		+ " perimeter: " + DoubleToString(GetPerimeter())
		+ " outline color: " + IntToHexNumber(GetOutlineColor());
	return shapeDescription;
}