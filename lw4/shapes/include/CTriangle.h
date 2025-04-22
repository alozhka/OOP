#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CTriangle final : public virtual ISolidShape
{
public:
	CTriangle(CPoint p1, CPoint p2, CPoint p3, uint32_t inlineColor, uint32_t outlineColor);

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;

	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetFilledColor() const override;
	[[nodiscard]] CPoint GetVertex1() const;
	[[nodiscard]] CPoint GetVertex2() const;
	[[nodiscard]] CPoint GetVertex3() const;

	[[nodiscard]] std::string ToString() const override;

	~CTriangle() override = default;

private:
	CPoint m_vertex1, m_vertex2, m_vertex3;
	double m_determinant;
	uint32_t m_filledColor, m_outlineColor;
};