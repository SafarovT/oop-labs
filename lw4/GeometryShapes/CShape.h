#pragma once
#include "IShape.h"

class CShape : virtual public IShape
{
public:
	CShape(uint32_t outlineColor, std::string shapeName)
		: m_outlineColor(outlineColor)
		, m_shapeName(std::move(shapeName)) //если по значению то std::move
	{

	}

	CShape(std::string shapeName)
		: m_shapeName(shapeName)
	{
	}

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
private:
	uint32_t m_outlineColor = 0;
	std::string m_shapeName;
};