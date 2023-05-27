#include "CRectangle.h"
#include <math.h>

double CRectangle::GetWidth() const
{
	return abs(m_rightBottom.x - m_leftTop.x);
}

double CRectangle::GetHeight() const
{
	return abs(m_rightBottom.y - m_leftTop.y);
}

double CRectangle::GetArea() const
{
	return GetHeight() * GetWidth();
}

double CRectangle::GetPerimeter() const
{
	return GetHeight() * 2 + GetWidth() * 2;
}

std::string CRectangle::ToString() const
{
	std::string rectangleInfo = CSolidShape::ToString();
	rectangleInfo += " Left top: " + m_leftTop.ToString() + " Right bottom: " + m_rightBottom.ToString();

	return rectangleInfo;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}

void CRectangle::Draw(ICanvas& canvas) const
{
	CPoint leftTopPoint = m_leftTop;
	CPoint rightBottomPoint = m_rightBottom;
	CPoint rightTopPoint(rightBottomPoint.x, leftTopPoint.y);
	CPoint leftBottomPoint(leftTopPoint.x, rightBottomPoint.y);
	std::vector<CPoint> vertexes = {
		leftTopPoint,
		rightTopPoint,
		rightBottomPoint,
		leftBottomPoint
	};

	canvas.FillPolygon(vertexes, GetFillColor(), GetOutlineColor());
}