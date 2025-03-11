#include "../lib/Dictionary.cpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

struct TestData
{
	std::string initial, actual;
};

TEST_CASE("Converts string to lower case", "[convert][positive]")
{
	TestData data = GENERATE(
		TestData("UPPER", "upper"),
		TestData("LoWeR 123123%#$@", "lower 123123%#$@"));

	REQUIRE(data.actual == ToLower(data.initial));
}