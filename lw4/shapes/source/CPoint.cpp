#include "../include/CPoint.h"

#include <cmath>

CPoint::CPoint(double x, double y)
{
	this->x = x;
	this->y = y;
}

double CPoint::Distance(const CPoint& a, const CPoint& b)
{
	return std::hypot(a.x - b.x, a.y - b.y);
}
