#pragma once

class CPoint
{
public:
	double x, y;

	CPoint(double x, double y);

	static double GetDistance(const CPoint& a, const CPoint& b);
};