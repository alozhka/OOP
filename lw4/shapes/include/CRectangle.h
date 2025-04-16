#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CRectangle final : public virtual ISolidShape
{
public:
	CRectangle(CPoint leftTopPoint, double width, double height, u_int32_t outlineColor, u_int32_t filledColor);

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;

	[[nodiscard]] u_int32_t GetOutlineColor() const override;
	[[nodiscard]] u_int32_t GetFilledColor() const override;
	[[nodiscard]] CPoint GetLeftTop() const;
	[[nodiscard]] CPoint GetRightBottom() const;
	[[nodiscard]] double GetWidth() const;
	[[nodiscard]] double GetHeight() const;

	[[nodiscard]] std::string ToString() const override;

	~CRectangle() override = default;

private:
	u_int32_t m_outlineColor, m_filledColor;
	double m_width, m_height;
	CPoint m_leftTopPoint;
};