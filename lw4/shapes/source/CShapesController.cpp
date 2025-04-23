#include "../include/CShapesController.h"

#include "../include/CCanvas.h"
#include "../include/CCircle.h"
#include "../include/CLineSegment.h"
#include "../include/CRectangle.h"
#include "../include/CTriangle.h"

#include <functional>
#include <sstream>

CShapesController::CShapesController(std::istream& input, std::ostream& output)
	: m_action_map{
		{ "rectangle", std::bind_front(&CShapesController::AddRectangle, this) },
		{ "circle", std::bind_front(&CShapesController::AddCircle, this) },
		{ "triangle", std::bind_front(&CShapesController::AddTriangle, this) },
		{ "line", std::bind_front(&CShapesController::AddLine, this) }
	}
	, m_input(input)
	, m_output(output)
{
}

void CShapesController::DrawShapes(sf::RenderWindow& window)
{
	CCanvas canvas(window);
	for (const std::unique_ptr<IShape>& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

void CShapesController::HandleInput()
{
	std::string command;
	std::getline(m_input, command);

	std::istringstream iss(command);
	std::string action;
	iss >> action;

	const auto it = m_action_map.find(action);
	if (it == m_action_map.end())
	{
		m_output << "Invalid command\n";
		return;
	}

	try
	{
		it->second(iss);
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
}

void CShapesController::PrintResults()
{
	if (m_shapes.empty())
	{
		m_output << "No shapes provided\n";
		return;
	}
}

void CShapesController::AddRectangle(std::istream& input)
{
	double x, y, width, height;
	uint32_t filledColor, outlineColor;

	if (!(input >> x >> y >> width >> height >> std::hex >> filledColor >> std::hex >> outlineColor))
	{
		throw std::invalid_argument("Invalid arguments. Usage: rectangle <x> <y> <width> <height> <inlineColor> <outlineColor>");
	}

	auto rect = std::make_unique<CRectangle>(CPoint{ x, y }, width, height, filledColor, outlineColor);
	m_shapes.push_back(std::move(rect));
}

void CShapesController::AddCircle(std::istream& input)
{
	double x, y, radius;
	uint32_t filledColor, outlineColor;

	if (!(input >> x >> y >> radius >> std::hex >> filledColor >> std::hex >> outlineColor))
	{
		throw std::invalid_argument("Invalid arguments. Usage: circle <x> <y> <radius>");
	}

	auto circle = std::make_unique<CCircle>(CPoint{ x, y }, radius, filledColor, outlineColor);
	m_shapes.push_back(std::move(circle));
}

void CShapesController::AddLine(std::istream& input)
{
	double x1, y1, x2, y2;
	uint32_t filledColor;

	if (!(input >> x1 >> y1 >> x2 >> y2 >> std::hex >> filledColor))
	{
		throw std::invalid_argument("Invalid arguments. Usage: line <x1> <y1> <x2> <y2> <inlineColor>");
	}

	auto line = std::make_unique<CLineSegment>(
		CPoint{ x1, y1 },
		CPoint{ x2, y2 },
		filledColor);
	m_shapes.push_back(std::move(line));
}

void CShapesController::AddTriangle(std::istream& input)
{
	double x1, y1, x2, y2, x3, y3;
	uint32_t filledColor, outlineColor;
	if (!(input >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> std::hex >> filledColor >> std::hex >> outlineColor))
	{
		throw std::invalid_argument("Invalid arguments. "
									"Usage: triangle <x1> <y1> <x2> <y2> <x3> <y3> <inlineColor> <outlineColor>");
	}

	auto triangle = std::make_unique<CTriangle>(
		CPoint{ x1, y1 },
		CPoint{ x2, y2 },
		CPoint{ x3, y3 },
		filledColor,
		outlineColor);
	m_shapes.push_back(std::move(triangle));
}