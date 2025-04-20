#include "../include/CCircle.h"

#include <numbers>
#include <complex>

CCircle::CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t filledColor)
	: m_outlineColor(outlineColor)
	, m_filledColor(filledColor)
	, m_radius(radius)
	, m_center(center)
{
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

uint32_t CCircle::GetFilledColor() const
{
	return m_filledColor;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}
