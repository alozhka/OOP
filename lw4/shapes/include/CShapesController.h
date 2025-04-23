#pragma once

#include "IShape.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <istream>
#include <regex>

class CShapesController
{
public:
	CShapesController(std::istream& input, std::ostream& output);
	void DrawShapes(sf::RenderWindow& window) const;
	void HandleInput();
	void PrintResults() const;

private:
	void AddRectangle(std::istream& input);
	void AddCircle(std::istream& input);
	void AddLine(std::istream& input);
	void AddTriangle(std::istream& input);

	[[nodiscard]] IShape* FindShapeWithMaxArea() const;
	[[nodiscard]] IShape* FindShapeWithMinPerimeter() const;

	static uint32_t ColorToInt(const std::string& colorStr);
	static void ThrowIfInvalidColorFormat(std::string_view color);

	using ActionMap = std::unordered_map<std::string, std::function<void(std::istream&)>>;

	ActionMap m_action_map;
	std::istream& m_input;
	std::ostream& m_output;
	std::vector<std::unique_ptr<IShape>> m_shapes;
};
