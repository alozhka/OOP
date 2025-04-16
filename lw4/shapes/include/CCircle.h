#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CCircle final : public ISolidShape
{
public:
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	u_int32_t GetOutlineColor() override;

	u_int32_t GetFilledColor() override;

	CPoint GetCenter();
	double GetRadius();
};