#include "../lib/converter.cpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

struct StringToIntTestData
{
	std::string str;
	int radix;
	int actual;
};

// String to int

TEST_CASE("Converts string to int with numeric system", "[positive]")
{
	const StringToIntTestData testData = GENERATE(
		StringToIntTestData{ "10", 10, 10 },
		StringToIntTestData{ "-10", 16, -16 },
		StringToIntTestData{ "ZZ", 36, 1295 },
		StringToIntTestData{ "0", 36, 0 },
		StringToIntTestData{ "2147483647", 10, 2147483647 },
		StringToIntTestData{ "-2147483648", 10, -2147483648 });

	REQUIRE(StringToInt(testData.str, testData.radix) == testData.actual);
}

TEST_CASE("Handles overflow", "[negative]")
{

	const StringToIntTestData data = GENERATE(
		StringToIntTestData{ "2147483648", 10 },
		StringToIntTestData{ "-2147483649", 10 });

	REQUIRE_THROWS_MATCHES(
		StringToInt(data.str, data.radix),
		std::overflow_error,
		Catch::Matchers::Message("Reached overflow"));
}

TEST_CASE("Cannot handle unsupported radix", "[negative]")
{
	const StringToIntTestData data = GENERATE(
		StringToIntTestData{ "123", -1, 1234 },
		StringToIntTestData{ "122", 37, 1223 });

	REQUIRE_THROWS_MATCHES(
		StringToInt(data.str, data.actual),
		std::invalid_argument,
		Catch::Matchers::Message("The base of the number system should be in the range from 2 to 36"));
}

// Int to string

struct IntToStringTestData
{
	int number;
	int radix;
	std::string actual;
};

TEST_CASE("Converts int to string with base", "[positive]")
{
	const IntToStringTestData data = GENERATE(
		IntToStringTestData{ 0, 2, "0" },
		IntToStringTestData{ 35, 36, "Z" },
		IntToStringTestData{-32, 10, "-32"});

	REQUIRE(IntToString(data.number, data.radix) == data.actual);
}

TEST_CASE("Cannot convert with unsupported base", "[negative]")
{
	const IntToStringTestData data = GENERATE(
		IntToStringTestData{ 35, 1, "1" },
		IntToStringTestData{ 0, 37, "1" });

	REQUIRE_THROWS_MATCHES(
		IntToString(data.number, data.radix) == data.actual,
		std::invalid_argument,
		Catch::Matchers::Message("The base of the number system should be in the range from 2 to 36"));
}