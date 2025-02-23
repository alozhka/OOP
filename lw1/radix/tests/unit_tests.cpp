#include "../lib/converter.cpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

struct TestData
{
	std::string str;
	int radix;
	int actual;
};

TEST_CASE("Converts string to int with numeric system", "[positive]")
{
	TestData testData = GENERATE(
		TestData{ "10", 10, 10 },
		TestData{ "10", 16, 16 },
		TestData{ "ZZ", 36, 1295 },
		TestData{ "0", 36, 0 },
		TestData{ "2147483647", 10, 2147483647 },
		TestData{ "-2147483648", 10, -2147483648 });

	REQUIRE(StringToInt(testData.str, testData.radix) == testData.actual);
}

TEST_CASE("Handles overflow", "[negative]")
{

	TestData testData = GENERATE(
		TestData{ "2147483648", 10 },
		TestData{ "-2147483649", 10 });

	REQUIRE_THROWS(StringToInt(testData.str, testData.radix), "Reached overflow");
}