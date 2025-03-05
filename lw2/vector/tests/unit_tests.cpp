#include "../lib/MyVector.h"
#include "catch2/generators/catch_generators.hpp"
#include "catch2/matchers/catch_matchers_exception.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <fstream>

struct TestData
{
	std::vector<double> expected;
	std::vector<double> actual;
};

/**
 * ReadNumbers
 */

TEST_CASE("Read numbers from stream", "[read][positive]")
{
	std::vector<double> expected = { 1.0, 2.0, 3.0 };
	std::vector<double> actual;
	std::ifstream in("../tests/input/1.txt");

	ReadNumbers(in, actual);
	in.close();

	REQUIRE(expected == actual);
}

// negative

TEST_CASE("Cannot read invalid number format", "[read][negative]")
{
	std::vector<double> actual;
	std::ifstream in("../tests/invalid/not-number.txt");

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

	ProcessNumbers(data.expected);

	REQUIRE(data.expected == data.actual);
}