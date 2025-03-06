#include "../lib/HtmlDecoder.cpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

TEST_CASE("Converts decoded HTML symbols", "[decode][positive]")
{
	REQUIRE("123\"123" == HtmlDecodeString("123&quot;123"));
	REQUIRE("123'123" == HtmlDecodeString("123&apos;123"));
	REQUIRE("123<123" == HtmlDecodeString("123&lt;123"));
	REQUIRE("123>123" == HtmlDecodeString("123&gt;123"));
	REQUIRE("123&123" == HtmlDecodeString("123&amp;123"));
	REQUIRE("\"1'2&3,<4>5&>&sample;a" == HtmlDecodeString("&quot;1&apos;2&amp;3&lt;4&gt;5&amp;gt;&sample;a"));

}