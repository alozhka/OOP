#include "../lib/Expression.h"
#include "catch2/matchers/catch_matchers_exception.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers.hpp>

struct TestData
{
	std::string expression;
	int expected;
};

TEST_CASE("Calculates expression", "[positive]")
{
	TestData data = GENERATE(
		TestData{ "(+ 7)", 7 },
		TestData{ "(+ 8)", 8 },
		TestData{ "(+ 2 3)", 5 },
		TestData{ "(+ 2 3 4)", 9 },
		TestData{ "(* 2 4)", 8 },
		TestData{ "(+ (* 2 3) (* 3 4))", 18 },
		TestData{ "(* (+ 1 2) (+ 3 1))", 12 },
		TestData{ "(+ 5 (* 2 3 2) (+ 5 (+ 2 5) (* 2 2) ))", 33 },
		TestData{ "(+ -2 3)", 1 }, TestData{ "(+ 40 40)", 80 });

	REQUIRE(data.expected == CalculateExpression(data.expression));
}

// Negative

TEST_CASE("Cannot convert invalid expression")
{
	REQUIRE_THROWS_MATCHES(
		CalculateExpression("(+ 7 9"),
		std::invalid_argument,
		Catch::Matchers::Message("Invalid expression"));
	REQUIRE_THROWS_MATCHES(
		CalculateExpression("(7 8 2)"),
		std::invalid_argument,
		Catch::Matchers::Message("Invalid operation"));
	REQUIRE_THROWS_MATCHES(
		CalculateExpression("("),
		std::invalid_argument,
		Catch::Matchers::Message("Invalid operation"));
	REQUIRE_THROWS_MATCHES(
		CalculateExpression("(+ notnumber)"),
		std::invalid_argument,
		Catch::Matchers::Message("Invalid number"));
}