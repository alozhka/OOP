#include "../include/Calculator.h"
#include "../include/CalculatorController.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_compiler_capabilities.hpp>
#include <catch2/internal/catch_test_registry.hpp>

TEST_CASE("Calculator computes functions", "[positive][calculator]")
{
	Calculator calc;
	calc.DefineVariable("five", 5);
	calc.DefineVariable("four", 4);
	calc.DefineVariable("eight", 8);

	calc.DefineFunction("testAdd", Operations::SUM, "five", "four");

	REQUIRE(9 == calc.GetValue("testAdd"));

	calc.DefineFunction("testMultiply", Operations::MULTIPLY, "testAdd", "eight");

	REQUIRE(72 == calc.GetValue("testMultiply"));
}

TEST_CASE("Controller handles commands", "[positive][calculator]")
{
	std::istringstream input(
		"var x\n"
		"print x\n"
		"let x=42\n"
		"print x\n"
		"let x=1.234\n"
		"print x\n"
		"let y=x\n"
		"let x=99\n"
		"printvars");
	std::ostringstream output;
	Calculator calc;
	CalculatorController controller(calc, input, output);

	controller.HandleInput();

	REQUIRE("nan\n42.00\n1.23\nx:99.00\ny:23.00\n" == output.str());
}

TEST_CASE("Calculator defines functions", "[positive][calculator]")
{
	std::istringstream input(
		"var x\n"
		"var y\n"
		"print x\n"
		"fn XPlusY=x+y\n"
		"print x\n"
		"let x=3\n"
		"let y=4\n"
		"print XPlusY\n"
		"let z=3.5\n"
		"fn XPlusYDivZ=XPlusY/z\n"
		"printfns");
	std::ostringstream output;
	Calculator calc;
	CalculatorController controller(calc, input, output);

	controller.HandleInput();

	REQUIRE("nan\n7.00\n14.00\nXPlusY:14.00\nXPlusYDivZ:4.00\n" == output.str());
}