#pragma once
#include "ISolidShape.h"
#include "CShape.h"

class CSolidShape : public CShape, public ISolidShape
{
public:
	CSolidShape(uint32_t outlineColor, uint32_t fillColor, std::string shapeName)
		: CShape(outlineColor, shapeName)
		, m_fillColor(fillColor)
	{
	}

	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	std::string ToString() const override;
private:
	uint32_t m_fillColor;
};