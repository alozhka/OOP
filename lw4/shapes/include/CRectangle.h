#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CRectangle final : public virtual ISolidShape
{
public:
	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;

	[[nodiscard]] u_int32_t GetOutlineColor() const override;
	[[nodiscard]] u_int32_t GetFilledColor() const override;
	[[nodiscard]] CPoint GetLeftTop() const;
	[[nodiscard]] CPoint GetRightTop() const;
	[[nodiscard]] CPoint GetRightBottom() const;
	[[nodiscard]] CPoint GetLeftBottom() const;

	[[nodiscard]] std::string ToString() const override;

	~CRectangle() override = default;
};