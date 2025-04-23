
#include "../include/CCircle.h"
#include "CMockCanvas.h"

#include <catch2/catch_test_macros.hpp>
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