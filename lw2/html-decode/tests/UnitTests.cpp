#include "../lib/HtmlDecoder.cpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

struct TestData
{
	std::string initial, expected;
};

TEST_CASE("Decode HTML symbols in string", "[decode][positive]")
{
	TestData data = GENERATE(
		TestData{ "1&quot;3", "1\"3" },
		TestData{ "1&apos;3", "1'3" },
		TestData{ "1&lt;3", "1<3" },
		TestData{ "1&gt;3", "1>3" },
		TestData{ "1&amp;3", "1&3" },
		TestData{ "1&something;3", "1&something;3" },
		TestData{ " &quot;1&apos;2&amp;3&lt;4&gt;5&amp;gt;&sample;a", " \"1'2&3<4>5&gt;&sample;a" });

	REQUIRE(data.expected == HtmlDecode(data.initial));
}

TEST_CASE("Decode HTML symbols in stream", "[decode][positive]")
{
	std::istringstream in("A &quot;B&apos;C&amp;D&lt;4&gt;5&amp;gt;&sample;a");
	std::ostringstream out;

	HtmlDecode(in, out);
	REQUIRE("A \"B'C&D<4>5&gt;&sample;a\n" == out.str());
}