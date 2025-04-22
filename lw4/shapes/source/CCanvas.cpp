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

void CCanvas::FillPolygon(const std::vector<CPoint>& points, uint32_t filledColor, uint32_t outlineColor) const
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());

	for (size_t i = 0; i < points.size(); i++)
	{
		const sf::Vector2f v(static_cast<float>(points[i].x), static_cast<float>(points[i].y));
		polygon.setPoint(i, v);
	}

	polygon.setFillColor(sf::Color(filledColor));
	polygon.setOutlineColor(sf::Color(outlineColor));
	polygon.setOutlineThickness(1.0f);

	m_window.draw(polygon);
}

void CCanvas::FillRectangle(CPoint coordinates, double width, double height, uint32_t filledColor, uint32_t outlineColor) const
{
	sf::RectangleShape rect(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
	rect.setPosition(sf::Vector2f(static_cast<float>(coordinates.x), static_cast<float>(coordinates.y)));
	rect.setFillColor(sf::Color(filledColor));
	rect.setOutlineColor(sf::Color(outlineColor));
	rect.setOutlineThickness(1.0f);

	m_window.draw(rect);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t filledColor, uint32_t outlineColor) const
{
	sf::CircleShape circle(static_cast<float>(radius));
	const sf::Vector2f pos(static_cast<float>(center.x), static_cast<float>(center.y));
	circle.setPosition(pos);
	circle.setFillColor(sf::Color(filledColor));
	circle.setOutlineColor(sf::Color(outlineColor));
	circle.setOutlineThickness(1.0f);

	m_window.draw(circle);
}