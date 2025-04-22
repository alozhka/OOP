#include "../include/CTriangle.h"
CTriangle::CTriangle(CPoint p1, CPoint p2, CPoint p3, uint32_t inlineColor, uint32_t outlineColor)
	: m_vertex1(p1)
	, m_vertex2(p2)
	, m_vertex3(p3)
	, m_filledColor(inlineColor)
	, m_outlineColor(outlineColor)
{
	m_determinant = (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	if (m_determinant == 0)
	{
		throw std::runtime_error("Invalid triangle coordinates");
	}
}

double CTriangle::GetArea() const
{
	return 0.5 * m_determinant * (m_determinant > 0 ? 1 : -1);
}

double CTriangle::GetPerimeter() const
{
	return CPoint::GetDistance(m_vertex1, m_vertex2)
		+ CPoint::GetDistance(m_vertex1, m_vertex3)
		+ CPoint::GetDistance(m_vertex2, m_vertex3);
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFilledColor() const
{
	return m_filledColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

std::string CTriangle::ToString() const
{
	return "Area: " + std::to_string(this->GetArea()) + " . Perimeter: " + std::to_string(this->GetPerimeter())
		+ "\nVertex 1: (" + std::to_string(GetVertex1().x) + ", " + std::to_string(GetVertex1().y) + ")\n"
		+ "Vertex 2: (" + std::to_string(GetVertex2().x) + ", " + std::to_string(GetVertex2().y) + ")\n"
		+ "Vertex 3: (" + std::to_string(GetVertex3().x) + ", " + std::to_string(GetVertex3().y) + ")\n";
}
