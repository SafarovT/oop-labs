#include "CPoint.h"
#include "common.h"

std::string CPoint::ToString() const
{
	return "(" + DoubleToString(x) + ", " + DoubleToString(y) + ")";
}
