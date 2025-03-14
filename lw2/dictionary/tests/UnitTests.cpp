#include "../cmake-build-debug/_deps/catch2-src/src/catch2/matchers/catch_matchers_string.hpp"
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

TEST_CASE("Reads data from stream", "[import][positive]")
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

TEST_CASE("Prints translation correctly", "[translation][positive]")
{
	const Dictionary initial = {
		{ "cat", { "кот", "кошка" } },
		{ "the red square", { "Красная площадь" } }
	};
	std::ostringstream oss;

	bool found = TryPrintTranslation(oss, initial, "cat");
	REQUIRE(found);
	REQUIRE("кот, кошка\n" == oss.str());

	oss.str("");
	found = TryPrintTranslation(oss, initial, "The Red Square");
	REQUIRE(found);
	REQUIRE("Красная площадь\n" == oss.str());

	oss.str("");
	found = TryPrintTranslation(oss, initial, "Not exists");
	REQUIRE(!found);
	REQUIRE(oss.str().empty());
}

TEST_CASE("Check russian and english strings", "[translate][negative]")
{
	REQUIRE(IsRussianString("Строка русская"));
	REQUIRE(!IsRussianString("Строка with english"));
	REQUIRE(!IsRussianString("Строка с 123"));

	REQUIRE(IsEnglishString("English string"));
	REQUIRE(!IsEnglishString("English and русский"));
	REQUIRE(!IsEnglishString("English and 123"));
}