#pragma once

#include "../include/ICanvas.h"
#include <ostream>

class CMockCanvas final : public ICanvas
{
public:
	explicit CMockCanvas(std::ostream& output);

	void DrawLine(CPoint from, CPoint to, uint32_t color) const override;
	void FillPolygon(const std::vector<CPoint>& points, uint32_t inlineColor, uint32_t outlineColor) const override;
	void FillRectangle(CPoint leftTop, double width, double height, uint32_t inlineColor, uint32_t outlineColor) const override;
	void FillCircle(CPoint center, double radius, uint32_t inlineColor, uint32_t outlineColor) const override;

private:
	std::ostream& m_output;
};
