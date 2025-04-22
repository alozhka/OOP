#include "../include/CRectangle.h"

CRectangle::CRectangle(CPoint leftTopPoint, double width, double height, uint32_t outlineColor, uint32_t filledColor)
	: m_outlineColor(outlineColor)
	, m_filledColor(filledColor)
	, m_width(width)
	, m_height(height)
	, m_leftTopPoint(leftTopPoint)
{
}

void CRectangle::Draw(ICanvas& canvas) const
{
	canvas.FillPolygon({ GetLeftTop(), GetRightBottom() }, GetFilledColor(), GetOutlineColor());
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2 * m_width * m_height;
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFilledColor() const
{
	return m_filledColor;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTopPoint;
}

CPoint CRectangle::GetRightBottom() const
{
	return { m_leftTopPoint.x + m_width, m_leftTopPoint.y + m_height };
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

std::string CRectangle::ToString() const
{
	return "Rectangle: Area - " + std::to_string(this->GetArea()) + "; Perimeter: " + std::to_string(this->GetPerimeter());
}
