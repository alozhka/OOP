#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CRectangle final : public virtual ISolidShape
{
public:
	CRectangle(CPoint leftTopPoint, double width, double height, uint32_t inlineColor, uint32_t outlineColor);

	void Draw(ICanvas& canvas) const override;

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetInlineColor() const override;
	[[nodiscard]] CPoint GetLeftTop() const;
	[[nodiscard]] CPoint GetRightBottom() const;
	[[nodiscard]] double GetWidth() const;
	[[nodiscard]] double GetHeight() const;

	[[nodiscard]] std::string ToString() const override;

	~CRectangle() override = default;

private:
	uint32_t m_outlineColor, m_inlineColor;
	double m_width, m_height;
	CPoint m_leftTopPoint;
};