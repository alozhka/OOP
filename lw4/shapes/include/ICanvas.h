#pragma once
#include "CPoint.h"

#include <vector>
#include <SFML/Graphics.hpp>

class ICanvas
{
public:
	virtual void DrawLine(CPoint from, CPoint to, uint32_t color) = 0;
	virtual void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) = 0;
	virtual void DrawCircle(CPoint center, double radius, uint32_t lineColor) = 0;
	virtual void FillCircle(CPoint center, double radius, uint32_t fillColor) = 0;

	virtual ~ICanvas() = default;
private:
	sf::RenderWindow& m_window;
};
