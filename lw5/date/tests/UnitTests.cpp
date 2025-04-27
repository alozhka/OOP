#include <CDate.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

namespace TestData
{
}

TEST_CASE("Date can be constructed differently", "[date][constructor]")
{
	auto defaultDate = CDate();
	REQUIRE(1970 == defaultDate.GetYear());
	REQUIRE(Month::JANUARY == defaultDate.GetMonth());
	REQUIRE(1 == defaultDate.GetDay());
	REQUIRE(WeekDay::THURSDAY == defaultDate.GetWeekDay());

	auto timestampDate = CDate(1222);
	REQUIRE(1973 == timestampDate.GetYear());
	REQUIRE(Month::MAY == timestampDate.GetMonth());
	REQUIRE(7 == timestampDate.GetDay());
	REQUIRE(WeekDay::MONDAY == timestampDate.GetWeekDay());

	auto specifiedDate = CDate(30, Month::JULY, 2010);
	REQUIRE(2010 == specifiedDate.GetYear());
	REQUIRE(Month::JULY == specifiedDate.GetMonth());
	REQUIRE(30 == specifiedDate.GetDay());
	REQUIRE(WeekDay::FRIDAY == specifiedDate.GetWeekDay());
}

TEST_CASE("Date can be increased", "[date][converter]")
{
	auto date = CDate();

	date++;
	REQUIRE(2 == date.GetDay());

	++date;
	REQUIRE(3 == date.GetDay());

	date += 5;
	REQUIRE(8 == date.GetDay());
}

TEST_CASE("Date can be decreased", "[date][converter]")
{
	auto date = CDate(15);

	date--;
	REQUIRE(15 == date.GetDay());

	--date;
	REQUIRE(14 == date.GetDay());

	date -= 5;
	REQUIRE(9 == date.GetDay());
}

// negative

TEST_CASE("Cannot construct invalid date", "[invalid][date]")
{
	std::function createInvalidDate = [] {
		return CDate(30, Month::FEBRUARY, 2005);
	};

	REQUIRE_THROWS_MATCHES(
		createInvalidDate(),
		std::invalid_argument,
		Catch::Matchers::Message("Invalid date"));
}