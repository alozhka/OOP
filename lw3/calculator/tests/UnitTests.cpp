#include "../include/Calculator.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_compiler_capabilities.hpp>
#include <catch2/internal/catch_test_registry.hpp>

TEST_CASE("Calculator computes functions", "[positive][calculator]")
{
	Calculator calc;
	calc.DefineVariable("five", 5);
	calc.DefineVariable("four", 4);
	calc.DefineVariable("eight", 8);

	calc.DefineBinaryFunction("testAdd", Operations::SUM, "five", "four");

	REQUIRE(9 == calc.GetValue("testAdd"));

	calc.DefineBinaryFunction("testMultiply", Operations::MULTIPLY, "testAdd", "eight");

	REQUIRE(72 == calc.GetValue("testMultiply"));
}
