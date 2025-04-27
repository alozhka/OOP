#include <CDate.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

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

	CDate newDate = date + 7;
	REQUIRE(15 == newDate.GetDay());
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

	CDate newDate = date - 7;
	REQUIRE(2 == newDate.GetDay());
}

TEST_CASE("Can compare dates together", "[date][comparison]")
{
	auto date1 = CDate(40);
	auto date2 = CDate(20);
	auto date3 = CDate(20);

	REQUIRE(date1 > date2);
	REQUIRE(date2 < date1);
	REQUIRE(date1 != date2);
	REQUIRE(date2 == date3);
	REQUIRE(date2 >= date3);
	REQUIRE(date2 <= date3);
}

TEST_CASE("Can parse date in `DD.MM.YYYY` format", "[date][parsing]")
{
	std::istringstream input("18.09.2024");
	CDate date{};

	input >> date;
	REQUIRE(2024 == date.GetYear());
	REQUIRE(Month::SEPTEMBER == date.GetMonth());
	REQUIRE(18 == date.GetDay());
}

TEST_CASE("Can print date in stream", "[date][print]")
{
	std::ostringstream output{};
	CDate date(31, Month::MARCH, 2002);

	output << date;
	REQUIRE(output.str() == "31.03.2002");
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

TEST_CASE("Cannot overcome date limit", "[invalid][date]")
{
	auto earlyDate = CDate(1);

	REQUIRE_THROWS_MATCHES(
		earlyDate - 2,
		std::out_of_range,
		Catch::Matchers::Message("Date is out of range"));
	REQUIRE_THROWS_MATCHES(
		earlyDate -= 2,
		std::out_of_range,
		Catch::Matchers::Message("Date is out of range"));
	--earlyDate;
	REQUIRE_THROWS_MATCHES(
		earlyDate--,
		std::out_of_range,
		Catch::Matchers::Message("Date is out of range"));

	auto lateDate = CDate(30, Month::DECEMBER, 9999);

	REQUIRE_THROWS_MATCHES(
		lateDate + 2,
		std::out_of_range,
		Catch::Matchers::Message("Date is out of range"));
	REQUIRE_THROWS_MATCHES(
		lateDate += 2,
		std::out_of_range,
		Catch::Matchers::Message("Date is out of range"));
	++lateDate;
	REQUIRE_THROWS_MATCHES(
		lateDate++,
		std::out_of_range,
		Catch::Matchers::Message("Date is out of range"));
}