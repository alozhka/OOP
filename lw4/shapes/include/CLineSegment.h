#pragma once
#include "CPoint.h"
#include "IShape.h"

class CLineSegment final : public IShape
{
public:
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	u_int32_t GetOutlineColor() override;

	CPoint GetStartPoint();
	CPoint GetEndPoint();
};