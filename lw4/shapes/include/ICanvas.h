#pragma once
#include "CPoint.h"

#include <SFML/Graphics.hpp>
#include <vector>

class ICanvas
{
public:
	virtual void DrawLine(CPoint from, CPoint to, uint32_t color) const = 0;
	virtual void FillPolygon(const std::vector<CPoint>& points, uint32_t filledColor, uint32_t outlineColor) const = 0;
	virtual void FillRectangle(CPoint leftTop, double width, double height, uint32_t filledColor, uint32_t outlineColor) const = 0;
	virtual void FillCircle(CPoint center, double radius, uint32_t filledColor, uint32_t outlineColor) const = 0;

	virtual ~ICanvas() = default;
};
