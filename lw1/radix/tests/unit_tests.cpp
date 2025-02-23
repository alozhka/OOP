#include "../lib/converter.cpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

TEST_CASE("Converts string to int with numeric system", "[positive][converter]")
{
	struct TestData
	{
		std::string str;
		int radix;
		int actual;
	};

	auto testData = GENERATE(
		TestData{ "10", 10, 10 });

	REQUIRE(StringToInt(testData.str, testData.radix) == testData.actual);
}