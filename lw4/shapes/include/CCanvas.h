#pragma once

#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class CCanvas final : public ICanvas
{
public:
	explicit CCanvas(sf::RenderWindow& window);

	void DrawLine(CPoint from, CPoint to, uint32_t color) const override;
	void FillPolygon(const std::vector<CPoint>& points, uint32_t inlineColor, uint32_t outlineColor) const override;
	void FillRectangle(CPoint coordinates, double width, double height, uint32_t inlineColor, uint32_t outlineColor) const override;
	void FillCircle(CPoint center, double radius, uint32_t inlineColor, uint32_t outlineColor) const override;

	~CCanvas() override = default;

private:
	sf::RenderWindow& m_window;
};