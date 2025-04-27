#include "catch2/matchers/catch_matchers_exception.hpp"

#include <CDate.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>

namespace TestData
{
const auto defaultDate = CDate();
}

TEST_CASE("Date can be constructed differently", "[date][constructor]")
{
	auto defaultDate = CDate();
	REQUIRE(1970 == defaultDate.GetYear());
	REQUIRE(Month::JANUARY == defaultDate.GetMonth());
	REQUIRE(1 == defaultDate.GetDay());

	auto timestampDate = CDate(1222);
	REQUIRE(1973 == timestampDate.GetYear());
	REQUIRE(Month::MAY == timestampDate.GetMonth());
	REQUIRE(7 == timestampDate.GetDay());

	auto specifiedDate = CDate(12, Month::AUGUST, 2005);
	REQUIRE(2005 == specifiedDate.GetYear());
	REQUIRE(Month::AUGUST == specifiedDate.GetMonth());
	REQUIRE(12 == specifiedDate.GetDay());
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

TEST_CASE("Cannot construct invalid date", "[date][converter]")
{
	std::function createInvalidDate = [] {
		return CDate(30, Month::FEBRUARY, 2005);
	};

	REQUIRE_THROWS_MATCHES(
		createInvalidDate(),
		std::invalid_argument,
		Catch::Matchers::Message("Invalid date"));
}