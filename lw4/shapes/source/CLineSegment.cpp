#include "../include/CLineSegment.h"

CLineSegment::CLineSegment(CPoint x, CPoint y, uint32_t color)
	: m_outlineColor(color)
	, m_startPoint(x)
	, m_endPoint(y)
{
}

void CLineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(GetStartPoint(), GetEndPoint(), GetOutlineColor());
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return CPoint::GetDistance(m_startPoint, m_endPoint);
}

std::string CLineSegment::ToString() const
{
	return "LineSegment: Area - " + std::to_string(this->GetArea()) + "; Perimeter - " + std::to_string(this->GetPerimeter());
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}
