#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CCircle final : public virtual ISolidShape
{
public:
	CCircle(CPoint center, double radius, uint32_t inlineColor, uint32_t outlineColor);

	void Draw(ICanvas& canvas) const override;

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetInlineColor() const override;
	[[nodiscard]] CPoint GetCenter() const;
	[[nodiscard]] double GetRadius() const;

	[[nodiscard]] std::string ToString() const override;

	~CCircle() override = default;

private:
	uint32_t m_outlineColor, m_inlineColor;
	double m_radius;
	CPoint m_center;
};