#include "../src/CMyArray.h"

#include <catch2/catch_test_macros.hpp>

constexpr size_t DEFAULT_CAPACITY = 10;

template <typename T>
void CompareArrayAndVector(const CMyArray<T>& left, const std::vector<T>& right)
{
	CHECK(left.Size() == right.size());

	size_t i = 0;
	for (T value : left)
	{
		CHECK(value == right[i++]);
	}
}

template <typename T>
void CompareArrays(const CMyArray<T>& left, const CMyArray<T>& right)
{
	CHECK(left.Size() == right.Size());
	CHECK(left.Capacity() == right.Capacity());

	auto leftIt = left.begin();
	for (T value : right)
	{
		CHECK(*leftIt == value);
		++leftIt;
	}
}

TEST_CASE("Constructs array", "[array][ctor]")
{
	SECTION("Default constructor does not allocate memory")
	{
		CMyArray<int> array{};

		CHECK(0 == array.Size());
		CHECK(0 == array.Capacity());
	}

	SECTION("Copy constructor")
	{
		CMyArray<int> array{};
		array.PushBack(5);
		array.PushBack(3);
		array.PushBack(-99);

		CMyArray copy(array);

		CompareArrays(copy, array);
	}

	SECTION("Copy assignment")
	{
		CMyArray<int> array{}, copy{};
		array.PushBack(5);
		array.PushBack(3);
		array.PushBack(-99);

		copy = array;

		CompareArrays(copy, array);
	}

	SECTION("Moving constructor")
	{
		CMyArray<int> array{};
		array.PushBack(5);
		array.PushBack(3);
		array.PushBack(-99);

		CMyArray moved{std::move(array)};

		CompareArrayAndVector(moved, { 5, 3, -99 });
		CompareArrayAndVector(array, {});
		CHECK(0 == array.Capacity());
	}
}