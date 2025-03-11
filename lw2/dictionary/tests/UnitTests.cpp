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

TEST_CASE("Reads data from memory", "[import][positive]")
{
	Dictionary expected = {
		{ "cat", { "кошка", "кот" } },
		{ "meow", { "кот", "к о т" } },
		{ "кот", { "cat", "meow" } },
		{ "к о т", { "meow" } },
		{ "кошка", { "cat" } }
	};
	std::istringstream ss("cat:кошка,кот\nmeow:кот,к о т\nкот:cat,meow\nк о т:meow\n");

	Dictionary actual = LoadDictionary(ss);
	REQUIRE(expected == actual);
}

TEST_CASE("Translate words from English to Russian and ", "[translate][positive]")
{
	Dictionary expected = {
		{ "cat", { "кошка", "кот" } },
		{ "meow", { "кот", "к о т" } },
		{ "кот", { "cat", "meow" } },
		{ "к о т", { "meow" } }
	};

	REQUIRE("кот, кошка");
}

/**
 * Negative
 */