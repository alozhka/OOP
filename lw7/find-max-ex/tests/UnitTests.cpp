#include "../src/CompareUtils.h"
#include "catch2/catch_test_macros.hpp"

struct Athlete
{
	std::string name{};
	ushort age = 0;
};

namespace TestData
{
std::function AthleteAgeComparator = [](const Athlete& a, const Athlete& b) { return a.age < b.age; };
} // namespace TestData

TEST_CASE("Finds max element by predicate", "[compare]")
{
}

// negative
TEST_CASE("Cannot find max element if vector is empty", "[compare]")
{
	std::vector<Athlete> athletes{};
	Athlete* max = nullptr;

	CHECK(!CompareUtils::FindMax(athletes, *max, TestData::AthleteAgeComparator));
	CHECK(max == nullptr);
}