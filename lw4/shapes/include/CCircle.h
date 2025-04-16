#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CCircle final : public virtual ISolidShape
{
public:
	CCircle(CPoint center, double radius, u_int32_t outlineColor, u_int32_t filledColor);

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;

	[[nodiscard]] u_int32_t GetOutlineColor() const override;
	[[nodiscard]] u_int32_t GetFilledColor() const override;
	[[nodiscard]] CPoint GetCenter() const;
	[[nodiscard]] double GetRadius() const;

	[[nodiscard]] std::string ToString() const override;

	~CCircle() override = default;

private:
	u_int32_t m_outlineColor, m_filledColor;
	double m_radius;
	CPoint m_center;
};