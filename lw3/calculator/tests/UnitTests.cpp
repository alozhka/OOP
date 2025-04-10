#include "../include/Calculator.h"
#include "../include/CalculatorController.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_compiler_capabilities.hpp>
#include <catch2/internal/catch_test_registry.hpp>

TEST_CASE("Calculator defines variables", "[positive][calculator]")
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

	REQUIRE("nan\n42.00\n1.23\nx:99.00\ny:1.23\n" == output.str());
}

TEST_CASE("Calculator defines functions", "[positive][calculator]")
{
	std::istringstream input(
		"var x\n"
		"var y\n"
		"fn XPlusY=x+y\n"
		"print XPlusY\n"
		"let x=3\n"
		"let y=4\n"
		"print XPlusY\n"
		"let x=10\n"
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

TEST_CASE("let computes value once, fn computes value each execution", "[positive][calculator]")
{
	std::istringstream input(
		"let v=42\n"
		"let variable=v\n"
		"fn function=v\n"
		"let v=43\n"
		"print variable\n"
		"print function\n");
	std::ostringstream output;
	Calculator calc;
	CalculatorController controller(calc, input, output);

	controller.HandleInput();

	REQUIRE("42.00\n43.00\n" == output.str());
}

TEST_CASE("Calculator combines variables and functions", "[positive][calculator]")
{
	std::istringstream input(
		"var radius\n"
		"let pi=3.14159265\n"
		"fn radiusSquared=radius*radius\n"
		"fn circleArea=pi*radiusSquared\n"
		"let radius=10\n"
		"print circleArea\n"
		"let circle10Area=circleArea\n"
		"let radius=20\n"
		"let circle20Area=circleArea\n"
		"printfns\n"
		"printvars\n");
	std::ostringstream output;
	Calculator calc;
	CalculatorController controller(calc, input, output);

	controller.HandleInput();

	REQUIRE("314.16\n"
			"circleArea:1256.64\n"
			"radiusSquared:400.00\n"
			"circle10Area:314.16\n"
			"circle20Area:1256.64\n"
			"pi:3.14\n"
			"radius:20.00\n"
		== output.str());
}

// negative

TEST_CASE("Cannot handle invalid command", "[negative][calculator]")
{
	std::istringstream input("unknowncommand");
	std::ostringstream output;
	Calculator calc;
	CalculatorController controller(calc, input, output);

	controller.HandleInput();

	REQUIRE("Unknown command\n" == output.str());
}

TEST_CASE("Cannot handle command with invalid syntax", "[negative][calculator]")
{
	std::istringstream input("var a\n"
							 "var b\n"
							 "fn func = b _ a\n"
							 "fn func = b / \n"
							 "let a = \n");
	std::ostringstream output;
	Calculator calc;
	CalculatorController controller(calc, input, output);

	controller.HandleInput();

	REQUIRE("Invalid usage\n"
			"Invalid usage\n"
			"Invalid usage\n"
		== output.str());
}

TEST_CASE("Cannot define expression with already present name", "[negative][calculator]")
{
	std::istringstream input("var a\n"
							 "var a\n"
							 "fn a = a\n"
							 "fn b = a\n"
							 "var b\n");
	std::ostringstream output;
	Calculator calc;
	CalculatorController controller(calc, input, output);

	controller.HandleInput();

	REQUIRE("Name already exists\n"
			"Name already exists\n"
			"Name already exists\n"
		== output.str());
}

TEST_CASE("Cannot use undefined expression", "[negative][calculator]")
{
	std::istringstream input("let b = a\n"
							 "var b\n"
							 "fn c = b / a\n"
							 "fn c = a / b\n");
	std::ostringstream output;
	Calculator calc;
	CalculatorController controller(calc, input, output);

	controller.HandleInput();

	REQUIRE("Name does not exist\n"
			"Name does not exist\n"
			"Name does not exist\n"
		== output.str());
}

TEST_CASE("Cannot divide on zero", "[negative][calculator]")
{
	std::istringstream input("let b = 3\n"
							 "let a = 0\n"
							 "fn c = b / a\n"
							 "printfns\n");
	std::ostringstream output;
	Calculator calc;
	CalculatorController controller(calc, input, output);

	controller.HandleInput();

	REQUIRE("c:nan\n"
		== output.str());
}
