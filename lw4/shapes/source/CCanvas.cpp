#include "../include/CCanvas.h"

CCanvas::CCanvas(sf::RenderWindow& window)
	: m_window(window)
{
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t color) const
{
	const sf::Vertex line[] = {
		sf::Vertex({ static_cast<float>(from.x), static_cast<float>(from.y) }, sf::Color(color)),
		sf::Vertex({ static_cast<float>(to.x), static_cast<float>(to.y) }, sf::Color(color)),
	};

	m_window.draw(line, 2, sf::PrimitiveType::Lines);
}

void CCanvas::FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) const
{
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor) const
{
}
void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor) const
{
}