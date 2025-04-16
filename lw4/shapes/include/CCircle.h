#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CCircle final : public virtual ISolidShape
{
public:
	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] u_int32_t GetOutlineColor() const override;

	[[nodiscard]] u_int32_t GetFilledColor() const override;

	CPoint GetCenter();
	double GetRadius();
};