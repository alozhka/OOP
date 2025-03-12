#include "../lib/Dictionary.cpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

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
	};
	std::istringstream ss("cat:кошка,кот\nmeow:кот,к о т\n");

	Dictionary actual = LoadDictionary(ss);

	REQUIRE(expected == actual);
}

TEST_CASE("Adds correct translation to dictionary", "[translate][positive]")
{
	Dictionary expected = {
		{ "cat", { "кот", "кошка" } },
		{ "the red square", { "Красная площадь" } }
	};
	Dictionary actual{};

	AddTranslation(actual, "cat", "кот");
	AddTranslation(actual, "cat", "кошка");
	AddTranslation(actual, "cat", "кот");
	AddTranslation(actual, "The Red Square", "Красная площадь");

	REQUIRE(expected == actual);
}