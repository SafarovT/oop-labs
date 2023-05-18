#include "CSolidShape.h"
#include "common.h"

uint32_t CSolidShape::GetOutlineColor() const
{
	return CShape::GetOutlineColor();
}

uint32_t CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

std::string CSolidShape::ToString() const
{
	std::string solidShapeInfo = CShape::ToString();
	solidShapeInfo += " Fill color: " + IntToHexNumber(GetFillColor());
	return solidShapeInfo;
}