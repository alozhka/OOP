
#include "../include/CCircle.h"
#include "../include/CLineSegment.h"
#include "../include/CRectangle.h"
#include "../include/CTriangle.h"
#include "CMockCanvas.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <numbers>

namespace TestData
{
constexpr double invalidRadius = -1;

constexpr uint32_t outlineColor = 0xFFFFFF;
constexpr uint32_t inlineColor = 0x6A6A6B;
constexpr double width = 50.0;
constexpr double height = 24.0;
constexpr double validRadius = 10.0;
constexpr double triangleArea = 6.0;
constexpr double trianglePerimetr = 12;

const CPoint firstPoint{ 13.0, 10.0 };
const CPoint secondPoint{ 10.0, 14.0 };
const CPoint thirdPoint{ 10.0, 10.0 };
} // namespace TestData

TEST_CASE("Can draw line", "[draw][line]")
{
	CLineSegment line(
		TestData::firstPoint,
		TestData::secondPoint,
		TestData::outlineColor);
	std::ostringstream oss;
	CMockCanvas canvas(oss);
	std::string expected = "Drawing line\nfrom: 13 10\nto: 10 14\ncolor: ffffff\n";

	line.Draw(canvas);

	REQUIRE(expected == oss.str());
	REQUIRE(line.GetStartPoint().x == TestData::firstPoint.x);
	REQUIRE(line.GetStartPoint().y == TestData::firstPoint.y);
	REQUIRE(line.GetEndPoint().x == TestData::secondPoint.x);
	REQUIRE(line.GetEndPoint().y == TestData::secondPoint.y);
	REQUIRE(line.GetArea() == 0);
	REQUIRE(line.GetPerimeter() == CPoint::GetDistance(TestData::firstPoint, TestData::secondPoint));
	REQUIRE(line.GetOutlineColor() == TestData::outlineColor);
}

TEST_CASE("Can draw circle", "[draw][circle]")
{
	CCircle circle(
		TestData::firstPoint,
		TestData::validRadius,
		TestData::inlineColor,
		TestData::outlineColor);
	std::ostringstream oss;
	CMockCanvas canvas(oss);
	std::string expected = "Filling circle\ncenter: 13 10\nradius: 10\ninline color: 6a6a6b\noutline color: ffffff\n";

	circle.Draw(canvas);

	REQUIRE(expected == oss.str());
	REQUIRE(circle.GetCenter().x == TestData::firstPoint.x);
	REQUIRE(circle.GetCenter().y == TestData::firstPoint.y);
	REQUIRE(circle.GetRadius() == TestData::validRadius);
	REQUIRE(circle.GetArea() == std::numbers::pi * std::pow(TestData::validRadius, 2));
	REQUIRE(circle.GetPerimeter() == 2 * std::numbers::pi * TestData::validRadius);
	REQUIRE(circle.GetInlineColor() == TestData::inlineColor);
	REQUIRE(circle.GetOutlineColor() == TestData::outlineColor);
}

TEST_CASE("Can draw rectangle", "[draw][rectangle]")
{
	CRectangle rect(
		TestData::firstPoint,
		TestData::width,
		TestData::height,
		TestData::inlineColor,
		TestData::outlineColor);
	std::ostringstream oss;
	CMockCanvas canvas(oss);
	std::string expected = "Filling rectangle\nleft top: 13 10\nwidth: 50\nheight: 24\ninline color: 6a6a6b\noutline color: ffffff\n";

	rect.Draw(canvas);

	REQUIRE(expected == oss.str());
	REQUIRE(rect.GetLeftTop().x == TestData::firstPoint.x);
	REQUIRE(rect.GetLeftTop().y == TestData::firstPoint.y);
	REQUIRE(rect.GetWidth() == TestData::width);
	REQUIRE(rect.GetHeight() == TestData::height);
	REQUIRE(rect.GetArea() == TestData::width * TestData::height);
	REQUIRE(rect.GetPerimeter() == 2 * (TestData::width + TestData::height));
	REQUIRE(rect.GetInlineColor() == TestData::inlineColor);
	REQUIRE(rect.GetOutlineColor() == TestData::outlineColor);
}

TEST_CASE("Can draw triangle", "[draw][triangle]")
{
	CTriangle triangle(
		TestData::firstPoint,
		TestData::secondPoint,
		TestData::thirdPoint,
		TestData::inlineColor,
		TestData::outlineColor);
	std::ostringstream oss;
	CMockCanvas canvas(oss);
	double expectedPerimeter = CPoint::GetDistance(TestData::firstPoint, TestData::thirdPoint)
		+ CPoint::GetDistance(TestData::secondPoint, TestData::thirdPoint)
		+ CPoint::GetDistance(TestData::firstPoint, TestData::secondPoint);
	double expectedArea = 0.5 * (TestData::firstPoint.x - TestData::thirdPoint.x)
			* (TestData::secondPoint.y - TestData::thirdPoint.y)
		- (TestData::secondPoint.x - TestData::thirdPoint.x)
			* (TestData::firstPoint.y - TestData::secondPoint.y);
	std::string expected = R"a(Filling polygon
points: coords: 13 10, coords: 10 14, coords: 10 10,
inline color: 6a6a6b
outline color: ffffff
)a";

	triangle.Draw(canvas);

	REQUIRE(expected == oss.str());
	REQUIRE(triangle.GetVertex1().x == TestData::firstPoint.x);
	REQUIRE(triangle.GetVertex1().y == TestData::firstPoint.y);
	REQUIRE(triangle.GetVertex2().x == TestData::secondPoint.x);
	REQUIRE(triangle.GetVertex2().y == TestData::secondPoint.y);
	REQUIRE(triangle.GetVertex3().x == TestData::thirdPoint.x);
	REQUIRE(triangle.GetVertex3().y == TestData::thirdPoint.y);
	REQUIRE(triangle.GetArea() == expectedArea);
	REQUIRE(triangle.GetPerimeter() == expectedPerimeter);
	REQUIRE(triangle.GetInlineColor() == TestData::inlineColor);
	REQUIRE(triangle.GetOutlineColor() == TestData::outlineColor);
}

// negative

TEST_CASE("Cannot create triangle with invalid coords", "[negative][draw][circle]")
{
	const std::function createTriangle = [] {
		return CTriangle(
			CPoint{ 50, 50 },
			CPoint{ 100, 100 },
			CPoint{ 120, 120 },
			TestData::inlineColor,
			TestData::outlineColor);
	};

	REQUIRE_THROWS_MATCHES(
		createTriangle(),
		std::runtime_error,
		Catch::Matchers::Message("Invalid triangle coordinates"));
}