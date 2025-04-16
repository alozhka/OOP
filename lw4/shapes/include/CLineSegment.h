#pragma once
#include "CPoint.h"
#include "IShape.h"

class CLineSegment final : public virtual IShape
{
public:
	CLineSegment(CPoint x, CPoint y, u_int32_t color);

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] u_int32_t GetOutlineColor() const override;

	[[nodiscard]] CPoint GetStartPoint() const;
	[[nodiscard]] CPoint GetEndPoint() const;

private:
	u_int32_t m_outlineColor;
	CPoint m_startPoint, m_endPoint;
};