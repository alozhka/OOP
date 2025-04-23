#pragma once
#include "IShape.h"

#include <istream>
#include <regex>

class CShapesController
{
public:
	CShapesController(std::istream& input, std::ostream& output);
	void DrawShapes(sf::RenderWindow& window);
	void HandleInput();
	void PrintResults();

private:
	void AddRectangle(std::istream& input);
	void AddCircle(std::istream& input);
	void AddLine(std::istream& input);
	void AddTriangle(std::istream& input);

	static uint32_t ColorToInt(const std::string& colorStr);
	static void ThrowIfInvalidColorFormat(std::string_view color);

	using ActionMap = std::unordered_map<std::string, std::function<void(std::istream&)>>;

	ActionMap m_action_map;
	std::istream& m_input;
	std::ostream& m_output;
	std::vector<std::unique_ptr<IShape>> m_shapes;
};
