#pragma once
#include "CPoint.h"
#include "IShape.h"

class CLineSegment final : public virtual IShape
{
public:
	CLineSegment(CPoint x, CPoint y, uint32_t color);

	void Draw(ICanvas& canvas) const override;

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] CPoint GetStartPoint() const;
	[[nodiscard]] CPoint GetEndPoint() const;

	[[nodiscard]] std::string ToString() const override;

	~CLineSegment() override = default;

private:
	uint32_t m_outlineColor;
	CPoint m_startPoint, m_endPoint;
};