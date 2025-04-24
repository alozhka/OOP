#include "../include/CShapesController.h"

#include "../include/CCanvas.h"
#include "../include/CCircle.h"
#include "../include/CLineSegment.h"
#include "../include/CRectangle.h"
#include "../include/CTriangle.h"

#include <functional>
#include <sstream>

namespace Regexes
{
static const std::regex COLOR_REGEX("^[0-9a-fA-F]{6}$");
}

CShapesController::CShapesController(std::istream& input, std::ostream& output)
	: m_actionMap{
		{ "rectangle", std::bind_front(&CShapesController::AddRectangle, this) },
		{ "circle", std::bind_front(&CShapesController::AddCircle, this) },
		{ "triangle", std::bind_front(&CShapesController::AddTriangle, this) },
		{ "line", std::bind_front(&CShapesController::AddLine, this) }
	}
	, m_input(input)
	, m_output(output)
{
}

void CShapesController::DrawShapes(sf::RenderWindow& window) const
{
	CCanvas canvas(window);
	for (const std::unique_ptr<IShape>& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

void CShapesController::ProcessShape()
{
	std::string command;
	std::getline(m_input, command);

	std::istringstream iss(command);
	std::string action;
	iss >> action;

	const auto it = m_actionMap.find(action);
	if (it == m_actionMap.end())
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

void CShapesController::PrintResults() const
{
	if (m_shapes.empty())
	{
		m_output << "No shapes provided\n";
		return;
	}

	m_output << "Shape with max area: \n";
	const IShape* maxAreaShape = FindShapeWithMaxArea();
	m_output << maxAreaShape->ToString() << std::endl;

	m_output << "Shape with min perimeter: \n";
	const IShape* minPerimeterShape = FindShapeWithMinPerimeter();
	m_output << minPerimeterShape->ToString() << std::endl;
}

void CShapesController::AddRectangle(std::istream& input)
{
	double x, y, width, height;
	std::string inlineColorStr, outlineColorStr;

	if (!(input >> x >> y >> width >> height >> inlineColorStr >> outlineColorStr))
	{
		throw std::invalid_argument("Invalid arguments. Usage: rectangle <x> <y> <width> <height> <inlineColor> <outlineColor>");
	}

	ThrowIfInvalidColorFormat(inlineColorStr);
	ThrowIfInvalidColorFormat(outlineColorStr);

	uint32_t inlineColor = ColorToInt(inlineColorStr);
	uint32_t outlineColor = ColorToInt(outlineColorStr);
	auto rect = std::make_unique<CRectangle>(CPoint{ x, y }, width, height, inlineColor, outlineColor);
	m_shapes.push_back(std::move(rect));
}

void CShapesController::AddCircle(std::istream& input)
{
	double x, y, radius;
	std::string inlineColorStr, outlineColorStr;

	if (!(input >> x >> y >> radius >> inlineColorStr >> outlineColorStr))
	{
		throw std::invalid_argument("Invalid arguments. Usage: circle <x> <y> <radius> <inlineColor> <outlineColor>");
	}

	ThrowIfInvalidColorFormat(inlineColorStr);
	ThrowIfInvalidColorFormat(outlineColorStr);

	uint32_t inlineColor = ColorToInt(inlineColorStr);
	uint32_t outlineColor = ColorToInt(outlineColorStr);
	auto circle = std::make_unique<CCircle>(CPoint{ x, y }, radius, inlineColor, outlineColor);
	m_shapes.push_back(std::move(circle));
}

void CShapesController::AddLine(std::istream& input)
{
	double x1, y1, x2, y2;
	std::string outlineColorStr;

	if (!(input >> x1 >> y1 >> x2 >> y2 >> outlineColorStr))
	{
		throw std::invalid_argument("Invalid arguments. Usage: line <x1> <y1> <x2> <y2> <outlineColor>");
	}

	ThrowIfInvalidColorFormat(outlineColorStr);

	uint32_t outlineColor = ColorToInt(outlineColorStr);
	auto line = std::make_unique<CLineSegment>(
		CPoint{ x1, y1 },
		CPoint{ x2, y2 },
		outlineColor);
	m_shapes.push_back(std::move(line));
}

void CShapesController::AddTriangle(std::istream& input)
{
	double x1, y1, x2, y2, x3, y3;
	std::string inlineColorStr, outlineColorStr;
	if (!(input >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> inlineColorStr >> outlineColorStr))
	{
		throw std::invalid_argument("Invalid arguments. "
									"Usage: triangle <x1> <y1> <x2> <y2> <x3> <y3> <inlineColor> <outlineColor>");
	}

	ThrowIfInvalidColorFormat(inlineColorStr);
	ThrowIfInvalidColorFormat(outlineColorStr);

	uint32_t inlineColor = ColorToInt(inlineColorStr);
	uint32_t outlineColor = ColorToInt(outlineColorStr);
	auto triangle = std::make_unique<CTriangle>(
		CPoint{ x1, y1 },
		CPoint{ x2, y2 },
		CPoint{ x3, y3 },
		inlineColor,
		outlineColor);
	m_shapes.push_back(std::move(triangle));
}

IShape* CShapesController::FindShapeWithMaxArea() const
{
	auto result = std::ranges::max_element(m_shapes, [](auto& a, auto& b) {
		return a->GetArea() < b->GetArea();
	});

	return result == m_shapes.end() ? nullptr : result->get();
}

IShape* CShapesController::FindShapeWithMinPerimeter() const
{
	auto result = std::ranges::min_element(m_shapes, [](auto& a, auto& b) {
		return a->GetPerimeter() < b->GetPerimeter();
	});

	return result == m_shapes.end() ? nullptr : result->get();
}

uint32_t CShapesController::ColorToInt(const std::string& colorStr)
{
	uint32_t num;
	std::stringstream ss;
	ss << std::hex << colorStr << "FF";
	ss >> num;
	return num;
}

void CShapesController::ThrowIfInvalidColorFormat(std::string_view color)
{
	if (!std::regex_match(color.data(), Regexes::COLOR_REGEX))
	{
		throw std::invalid_argument("Invalid color format.");
	}
}
