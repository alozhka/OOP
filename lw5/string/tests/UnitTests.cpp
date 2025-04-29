#include <CMyString.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Constructs string", "[string][constructor]")
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

		CMyString copy(initial);

		CHECK(copy.GetCapacity() == 8);
		CHECK(copy.GetLength() == 7);
		CHECK(std::strcmp(copy.GetStringData(), "1234567") == 0);
		CHECK(initial.GetCapacity() == 8);
		CHECK(initial.GetLength() == 7);
		CHECK(std::strcmp(initial.GetStringData(), "1234567") == 0);
	}

	SECTION("Move constructor")
	{
		CMyString initial("1234567");

		CMyString copy(std::move(initial));

		CHECK(copy.GetCapacity() == 8);
		CHECK(copy.GetLength() == 7);
		CHECK(std::strcmp(copy.GetStringData(), "1234567") == 0);
		CHECK(initial.GetCapacity() == 1);
		CHECK(initial.GetLength() == 0);
		CHECK(std::strcmp(initial.GetStringData(), "") == 0);
	}
}

TEST_CASE("Creates and moves strings", "[string]")
{
	SECTION("Copy assignment")
	{
		CMyString initial("1234567");

		CMyString copy = initial;

		CHECK(copy.GetCapacity() == 8);
		CHECK(copy.GetLength() == 7);
		CHECK(std::strcmp(copy.GetStringData(), "1234567") == 0);
		CHECK(initial.GetCapacity() == 8);
		CHECK(initial.GetLength() == 7);
		CHECK(std::strcmp(initial.GetStringData(), "1234567") == 0);

		copy = copy;

		CHECK(copy.GetCapacity() == 8);
		CHECK(copy.GetLength() == 7);
		CHECK(std::strcmp(copy.GetStringData(), "1234567") == 0);
	}

	SECTION("Move assignment")
	{
		CMyString initial("1234567");

		CMyString copy = std::move(initial);

		CHECK(copy.GetCapacity() == 8);
		CHECK(copy.GetLength() == 7);
		CHECK(std::strcmp(copy.GetStringData(), "1234567") == 0);
		CHECK(initial.GetCapacity() == 1);
		CHECK(initial.GetLength() == 0);
		CHECK(std::strcmp(initial.GetStringData(), "") == 0);
	}
}

TEST_CASE("Performs operations")
{
	SECTION("Computes substring", "[string][substring]")
	{
		CMyString initial("1234567");
		CMyString substr = initial.SubString(2, 4);

		CHECK(initial.GetCapacity() == 8);
		CHECK(initial.GetLength() == 7);
		CHECK(std::strcmp(initial.GetStringData(), "1234567") == 0);
		CHECK(substr.GetCapacity() == 5);
		CHECK(substr.GetLength() == 4);
		CHECK(std::strcmp(substr.GetStringData(), "3456") == 0);
	}

	SECTION("Cannot compute out of range substring", "[string][substring][negative]")
	{
		CMyString initial("1234567");
		CHECK_THROWS_AS(initial.SubString(3, 1), std::out_of_range);
		CHECK_THROWS_AS(initial.SubString(5, 8), std::out_of_range);
	}

	SECTION("Clears string", "[string]")
	{
		CMyString str("1234567");

		CHECK(str.GetCapacity() == 8);
		CHECK(str.GetLength() == 7);
		CHECK(std::strcmp(str.GetStringData(), "1234567") == 0);

		str.Clear();

		CHECK(str.GetCapacity() == 1);
		CHECK(str.GetLength() == 0);
		CHECK(std::strcmp(str.GetStringData(), "") == 0);
	}

	SECTION("Comparison operators")
	{
		CMyString str1("123123");
		CMyString str2("123412");
		CMyString str3("123123");

		CHECK(str1 == str1);
		CHECK(str1 == str3);
		CHECK_FALSE(str1 == str2);

		CHECK(str1 != str2);
		CHECK_FALSE(str1 != str3);
		CHECK_FALSE(str2 != str2);

		CHECK(str1 < str2);
		CHECK_FALSE(str1 < str1);
		CHECK_FALSE(str1 < str3);

		CHECK_FALSE(str1 > str2);
		CHECK_FALSE(str1 > str1);
		CHECK_FALSE(str1 > str3);
		CHECK(str2 > str1);

		CHECK(str1 <= str2);
		CHECK(str1 <= str1);
		CHECK(str1 <= str3);

		CHECK_FALSE(str1 >= str2);
		CHECK(str1 >= str1);
		CHECK(str1 >= str3);
		CHECK(str2 >= str1);
	}

	SECTION("Addition operators")
	{
		CMyString str1("123");
		CMyString str2(" 456");

		CMyString result = str1 + str2;

		CHECK(result.GetCapacity() == 8);
		CHECK(result.GetLength() == 7);
		CHECK(std::strcmp(result.GetStringData(), "123 456") == 0);

		result = str1 + std::string(" 456");

		CHECK(result.GetCapacity() == 8);
		CHECK(result.GetLength() == 7);
		CHECK(std::strcmp(result.GetStringData(), "123 456") == 0);

		result = str1 + " 456";

		CHECK(result.GetCapacity() == 8);
		CHECK(result.GetLength() == 7);
		CHECK(std::strcmp(result.GetStringData(), "123 456") == 0);

		result = str1;
		result += str2;

		CHECK(result.GetCapacity() == 8);
		CHECK(result.GetLength() == 7);
		CHECK(std::strcmp(result.GetStringData(), "123 456") == 0);
	}

	SECTION("Access via number index")
	{
		CMyString str("123456");

		CHECK(str[0] == '1');
		str[0] = 'A';
		CHECK(str[0] == 'A');
		CHECK(std::strcmp(str.GetStringData(), "A23456") == 0);
	}

	SECTION("Cannot access via out of range index")
	{
		CMyString str("123456");

		CHECK_THROWS_AS(str[7], std::out_of_range);
	}

	SECTION("Work with streams")
	{
		std::ostringstream oss;
		CMyString str("123 456");

		oss << str;

		CHECK(oss.str() == "123 456");

		std::istringstream is("123test");
		CMyString str2;

		is >> str2;

		CHECK(std::strcmp(str2.GetStringData(), "123test") == 0);
	}
}