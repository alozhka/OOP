#include "../lib/MyVector.h"
#include <catch2/catch_test_macros.hpp>
#include <fstream>

TEST_CASE("Read numbers from stream", "[read][positive]")
{
	std::vector<double> expected = {1.0, 2.0, 3.0};
	std::vector<double> actual;
	std::ifstream in("../tests/input/1.txt");

	ReadNumbers(in, actual);
	in.close();

	REQUIRE(expected == actual);
}