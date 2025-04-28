#include <CMyString.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Can construct string", "[UnitTests]")
{
	SECTION("Default constructor")
	{
		CMyString str;
		CHECK(str.GetCapacity() == 1);
		CHECK(str.GetLength() == 0);
		CHECK(std::strcmp(str.GetStringData(), "\0") == 0);
	}
}