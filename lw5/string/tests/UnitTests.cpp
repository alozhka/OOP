#include <CMyString.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Can construct string", "[UnitTests]")
{
	SECTION("Default constructor")
	{
		CMyString str;

		CHECK(str.GetCapacity() == 1);
		CHECK(str.GetLength() == 0);
		CHECK(std::strcmp(str.GetStringData(), "") == 0);
	}

	SECTION("Raw char constructor")
	{
		CMyString str("abc Def");

		CHECK(str.GetCapacity() == 8);
		CHECK(str.GetLength() == 7);
		CHECK(std::strcmp(str.GetStringData(), "abc Def") == 0);
	}

	SECTION("Raw string constructor with length")
	{
		CMyString str("1234567", 5);

		CHECK(str.GetCapacity() == 6);
		CHECK(str.GetLength() == 5);
		CHECK(std::strcmp(str.GetStringData(), "12345") == 0);
	}

	SECTION("stl::string constructor")
	{
		std::string stlString("1234567", 5);
		CMyString str(stlString);

		CHECK(str.GetCapacity() == 6);
		CHECK(str.GetLength() == stlString.size());
		CHECK(std::strcmp(str.GetStringData(), stlString.c_str()) == 0);
	}

	SECTION("Copy constructor")
	{
		CMyString initial("1234567");
		CMyString copy = initial;

		CHECK(initial.GetCapacity() == initial.GetCapacity());
		CHECK(initial.GetLength() == initial.GetLength());
		CHECK(std::strcmp(initial.GetStringData(), initial.GetStringData()) == 0);
	}

	SECTION("Move constructor")
	{
		CMyString initial("1234567");
		CMyString copy = std::move(initial);

		CHECK(copy.GetCapacity() == 8);
		CHECK(copy.GetLength() == 7);
		CHECK(std::strcmp(copy.GetStringData(), "1234567") == 0);
		CHECK(initial.GetCapacity() == 0);
		CHECK(initial.GetLength() == 0);
		CHECK(std::strcmp(initial.GetStringData(), "") == 0);
	}
}