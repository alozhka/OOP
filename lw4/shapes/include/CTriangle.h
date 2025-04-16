#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CTriangle final : public virtual ISolidShape
{
public:
	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] u_int32_t GetOutlineColor() const override;

	[[nodiscard]] u_int32_t GetFilledColor() const override;

	[[nodiscard]] CPoint GetVertex1() const;
	[[nodiscard]] CPoint GetVertex2() const;
	[[nodiscard]] CPoint GetVertex3() const;
};