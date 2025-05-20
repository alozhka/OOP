#include "../src/CompareUtils.h"
#include "catch2/catch_test_macros.hpp"

struct Athlete
{
	std::string name{};
	ushort age = 0;
	ushort weight = 0;

	bool operator==(const Athlete& other) const
	{
		return name == other.name && age == other.age && weight == other.weight;
	}
};

namespace TestData
{
std::function AthleteMaxAgeComparator = [](const Athlete& a, const Athlete& b) { return a.age > b.age; };
std::function AthleteMaxWeightComparator = [](const Athlete& a, const Athlete& b) { return a.weight > b.weight; };
std::function AthleteMaxNameComparator = [](const Athlete& a, const Athlete& b) { return a.name > b.name; };

Athlete Alex = { "Александр", 22, 79 };
Athlete Vladimir = { "Владимир", 30, 70 };
Athlete Yaroslav = { "Ярослав", 19, 66 };
std::vector Athletes = { Alex, Vladimir, Yaroslav };
} // namespace TestData

TEST_CASE("Finds max element by predicate", "[compare]")
{
	Athlete max{};

	CHECK(CompareUtils::FindMax(TestData::Athletes, max, TestData::AthleteMaxAgeComparator));
	CHECK(max == TestData::Vladimir);

	CHECK(CompareUtils::FindMax(TestData::Athletes, max, TestData::AthleteMaxNameComparator));
	CHECK(max == TestData::Yaroslav);

	CHECK(CompareUtils::FindMax(TestData::Athletes, max, TestData::AthleteMaxWeightComparator));
	CHECK(max == TestData::Alex);
}

// negative
TEST_CASE("Cannot find max element if vector is empty", "[compare][empty]")
{
	std::vector<Athlete> athletes{};
	Athlete* max = nullptr;

	CHECK(!CompareUtils::FindMax(athletes, *max, TestData::AthleteMaxAgeComparator));
	CHECK(max == nullptr);
}