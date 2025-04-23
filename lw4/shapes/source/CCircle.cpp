#include "../include/CCircle.h"

#include <numbers>
#include <complex>

CCircle::CCircle(CPoint center, double radius, uint32_t inlineColor, uint32_t outlineColor)
	: m_outlineColor(outlineColor)
	, m_inlineColor(inlineColor)
	, m_radius(radius)
	, m_center(center)
{
}

void CCircle::Draw(ICanvas& canvas) const
{
	canvas.FillCircle(GetCenter(), GetRadius(), GetInlineColor(), GetOutlineColor());
}

double CCircle::GetArea() const
{
	return std::numbers::pi * std::pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return 2 * std::numbers::pi * m_radius;
}

std::string CCircle::ToString() const
{
	return "Circle: Area - " + std::to_string(this->GetArea()) + "; Perimeter - " + std::to_string(this->GetPerimeter());
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetInlineColor() const
{
	return m_inlineColor;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}
