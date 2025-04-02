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
	std::istringstream input("var x\nprint x\nlet x=42\nprint x\nlet x=1.234\nprint x\nlet y=x\nlet x=99\nprintvars");
	std::ostringstream output;
	Calculator calc;
	CalculatorController controller(calc, input, output);

	controller.HandleInput();

	REQUIRE("nan\n42.00\n1.23\nx:99.00\ny:23.00\n" == output.str());
}