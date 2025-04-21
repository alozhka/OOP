#pragma once
#include "IShape.h"

#include <istream>

class CShapesController
{
public:
	CShapesController(std::istream& input, std::ostream& output);
	void DrawShapes();
	void HandleInput();
	void PrintResults();

private:
	void AddRectangle(std::string_view args);
	using ActionMap = std::unordered_map<std::string, std::function<void(std::string)>>;

	ActionMap m_action_map;
	std::istream& m_input;
	std::ostream& m_output;
	std::vector<std::unique_ptr<IShape>> m_shapes;
};
