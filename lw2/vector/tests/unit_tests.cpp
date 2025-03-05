#include "../lib/MyVector.h"
#include "catch2/matchers/catch_matchers_exception.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <fstream>

/**
 * ReadNumbers
 */

TEST_CASE("Read numbers from stream", "[read][positive]")
{
	std::vector<double> expected = {1.0, 2.0, 3.0};
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