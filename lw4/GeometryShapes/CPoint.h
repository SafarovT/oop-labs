#pragma once
#include <string>

class CPoint
{
public:
	CPoint() = default;

	CPoint(double const initialX, double const initialY)
	{
		x = initialX;
		y = initialY;
	}

	std::string ToString() const;

	double y = 0;
	double x = 0;
};