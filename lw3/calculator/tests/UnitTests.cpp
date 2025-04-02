#include "../include/Calculator.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_compiler_capabilities.hpp>
#include <catch2/internal/catch_test_registry.hpp>

TEST_CASE("Calculator can sum", "[positive][calculator]")
{
	Calculator calc;
	calc.DefineBinaryFunction("testAdd", Operations::SUM, 5, 4);
	const double result = calc.GetValue("testAdd");

	REQUIRE(result == 9);
}
