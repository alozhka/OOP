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
	// название
	void ProcessShape();
	// название
	void PrintResults() const;

private:
	void AddRectangle(std::istream& input);
	void AddCircle(std::istream& input);
	void AddLine(std::istream& input);
	void AddTriangle(std::istream& input);

	// sharedptr
	[[nodiscard]] IShape* FindShapeWithMaxArea() const;
	// sharedptr
	[[nodiscard]] IShape* FindShapeWithMinPerimeter() const;

	// вынести в cpp
	static uint32_t ColorToInt(const std::string& colorStr);
	static void ThrowIfInvalidColorFormat(std::string_view color);

	using ActionMap = std::unordered_map<std::string, std::function<void(std::istream&)>>;

	ActionMap m_actionMap;
	std::istream& m_input;
	std::ostream& m_output;
	std::vector<std::unique_ptr<IShape>> m_shapes;
};
