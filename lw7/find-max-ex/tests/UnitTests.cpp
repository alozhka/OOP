#include "../src/CompareUtils.h"
#include "catch2/catch_test_macros.hpp"

struct Athlete
{
	std::string name{};
	ushort height = 0;
	ushort weight = 0;

	bool operator==(const Athlete& other) const
	{
		return name == other.name && height == other.height && weight == other.weight;
	}
};

namespace TestData
{
std::function MaxHeightComparator = [](const Athlete& a, const Athlete& b) { return a.height < b.height; };
std::function AthleteMaxWeightComparator = [](const Athlete& a, const Athlete& b) { return a.weight < b.weight; };
std::function AthleteMaxNameComparator = [](const Athlete& a, const Athlete& b) { return a.name < b.name; };

Athlete Alex = { "Александр", 172, 79 };
Athlete Vladimir = { "Владимир", 180, 70 };
Athlete Yaroslav = { "Ярослав", 169, 66 };

std::vector Athletes = { Alex, Vladimir, Yaroslav };
} // namespace TestData

TEST_CASE("Finds max element by predicate", "[compare]")
{
	Athlete max{};

	CHECK(CompareUtils::FindMax(TestData::Athletes, max, TestData::MaxHeightComparator));
	CHECK(max == TestData::Vladimir);

	CHECK(CompareUtils::FindMax(TestData::Athletes, max, TestData::AthleteMaxNameComparator));
	CHECK(max == TestData::Yaroslav);

	CHECK(CompareUtils::FindMax(TestData::Athletes, max, TestData::AthleteMaxWeightComparator));
	CHECK(max == TestData::Alex);

	CHECK(CompareUtils::FindMax({ TestData::Yaroslav }, max, TestData::AthleteMaxNameComparator));
	CHECK(max == TestData::Yaroslav);
}

TEST_CASE("Supports commit-or-rollback functionality", "[compare][exceptions]")
{
	int max = 6;
	std::function comparatorWithException = [](int a, int b) {
		static int counter = 0;
		if (counter++ == 1)
		{
			throw std::runtime_error("Failed to compare integers");
		}
		return a < b;
	};

	CHECK_THROWS_AS(CompareUtils::FindMax({ 33, 10, 66, 8, 100 }, max, comparatorWithException), std::runtime_error);
	CHECK(max == 6);
}

// negative
TEST_CASE("Cannot find max element if vector is empty", "[compare][empty]")
{
	std::vector<Athlete> athletes{};
	Athlete* max = nullptr;

	CHECK(!CompareUtils::FindMax(athletes, *max, TestData::MaxHeightComparator));
	CHECK(max == nullptr);
}