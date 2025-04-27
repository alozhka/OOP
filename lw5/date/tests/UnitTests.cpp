#include <CDate.h>
#include <catch2/catch_test_macros.hpp>

namespace TestData
{
const auto defaultDate = CDate();
}

TEST_CASE("Date can be increased", "[date][converter]")
{
	CDate date = TestData::defaultDate;

	date++;
	REQUIRE(2 == date.GetDay());

	++date;
	REQUIRE(3 == date.GetDay());

	date += 5;
	REQUIRE(8 == date.GetDay());
}