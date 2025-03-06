#include "../lib/MyVector.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

struct TestData
{
	std::vector<double> initial;
	std::vector<double> expected;
};

/**
 * ReadNumbers
 */

TEST_CASE("Read numbers from stream", "[read][positive]")
{
	std::vector<double> expected = { 1.0, 2.0, 3.0 };
	std::vector<double> actual;
	std::istringstream in("1 2 3");

	ReadNumbers(in, actual);

	REQUIRE(expected == actual);
}

// negative

TEST_CASE("Cannot read invalid number format", "[read][negative]")
{
	std::vector<double> actual;
	std::istringstream in("1 2 4 1a0");

	REQUIRE_THROWS_MATCHES(ReadNumbers(in, actual), std::invalid_argument, Catch::Matchers::Message("ERROR"));
}

/**
 * ProcessNumbers
 */

TEST_CASE("Multiply for max element and divide for min element every element in collection", "[process][positive]")
{
	TestData data = GENERATE(
		TestData{ { 1.0, 2.0, 3.0 }, { 3.000, 6.000, 9.000 } },
		TestData{ { 3.5, 1, 2, -1 }, { -12.250, -3.500, -7.000, 3.500 } },
		TestData{ {}, {} });

	ProcessNumbers(data.initial);

	REQUIRE(data.expected == data.initial);
}

TEST_CASE("Cannot multiply if min = 0", "[process][positive]")
{
	TestData data = GENERATE(
		TestData{ { 1.0, 0, 3.0 }, { 3.000, 6.000, 9.000 } });

	REQUIRE_THROWS_MATCHES(ProcessNumbers(data.initial), std::invalid_argument, Catch::Matchers::Message("ERROR"));
}

/**
 * Sort numbers
 */

TEST_CASE("Sorts vector", "[sort][positive]")
{
	TestData data = GENERATE(TestData{ { -12.250, -3.500, -7.000, 3.500 }, { -12.250, -7.000, -3.500, 3.500 } });

	SortNumbers(data.initial);

	REQUIRE(data.expected == data.initial);
}

/**
 * Print numbers
 */

TEST_CASE("Prints vector", "[print][positive]")
{
	std::vector<double> initial = { -12.250, -7.000, -3.500, 3.500 };
	std::string expected = "-12.250 -7.000 -3.500 3.500\n";
	std::ostringstream out;

	PrintNumbers(out, initial);
	REQUIRE(expected == out.str());
}