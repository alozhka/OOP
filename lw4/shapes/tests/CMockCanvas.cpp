#include "CMockCanvas.h"

CMockCanvas::CMockCanvas(std::ostream& output)
	: m_output(output)
{
}

void CMockCanvas::DrawLine(CPoint from, CPoint to, uint32_t color) const
{
	m_output << "Drawing line\n"
			 << "from: " << from.x << " " << from.y << "\n"
			 << "to: " << to.x << " " << to.y << "\n"
			 << "color: " << std::hex << color << "\n";
}

void CMockCanvas::FillPolygon(const std::vector<CPoint>& points, uint32_t inlineColor, uint32_t outlineColor) const
{
	m_output << "Filling polygon\n"
			 << "points:\n";

	for (const CPoint p : points)
	{
		m_output << "coords: " << p.x << " " << p.y << "\n";
	}

	m_output << "inline color: " << inlineColor << "\n"
			 << "outline color: " << outlineColor << "\n";
}

void CMockCanvas::FillRectangle(CPoint leftTop, double width, double height, uint32_t inlineColor, uint32_t outlineColor) const
{
	m_output << "Filling rectangle\n"
			 << "left top: " << leftTop.x << " " << leftTop.y << "\n"
			 << "width: " << width << "\n"
			 << "height: " << height << "\n"
			 << "inline color: " << std::hex << inlineColor << "\n"
			 << "outline color: " << std::hex << outlineColor << "\n";
}

void CMockCanvas::FillCircle(CPoint center, double radius, uint32_t inlineColor, uint32_t outlineColor) const
{
	m_output << "Filling circle\n"
			 << "center: " << center.x << " " << center.y << "\n"
			 << "radius: " << radius << "\n"
			 << "inline color: " << std::hex << inlineColor << "\n"
			 << "outline color: " << std::hex << outlineColor << "\n";
}