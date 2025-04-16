#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CTriangle final : public ISolidShape
{
public:
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	u_int32_t GetOutlineColor() override;

	u_int32_t GetFilledColor() override;

	CPoint GetVertex1();
	CPoint GetVertex2();
	CPoint GetVertex3();
};