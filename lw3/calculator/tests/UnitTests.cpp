#include "../include/Calculator.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_compiler_capabilities.hpp>
#include <catch2/internal/catch_test_registry.hpp>

TEST_CASE("Calculator can sum", "[positive][calculator]")
{
	Calculator calc;
	auto five = Variable(5);
	auto four = Variable(4);
	calc.DefineBinaryFunction("testAdd", Operations::SUM, &five, &four);
	const double result = calc.GetValue("testAdd");

	REQUIRE(result == 9);
}
