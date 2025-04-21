#pragma once
#include "ICanvas.h"

class CCanvas final : public ICanvas
{
public:
	explicit CCanvas(sf::RenderWindow& window);

	void DrawLine(CPoint from, CPoint to, uint32_t color) const override;
	void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) const override;
	void DrawCircle(CPoint center, double radius, uint32_t lineColor) const override;
	void FillCircle(CPoint center, double radius, uint32_t fillColor) const override;

	~CCanvas() override = default;

private:
	sf::RenderWindow& m_window;
};