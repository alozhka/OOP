#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CRectangle final : public ISolidShape
{
public:
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	u_int32_t GetOutlineColor() override;

	u_int32_t GetFilledColor() override;

	CPoint GetLeftTop();
	CPoint GetRightTop();
	CPoint GetRightBottom();
	CPoint GetLeftBottom();
};