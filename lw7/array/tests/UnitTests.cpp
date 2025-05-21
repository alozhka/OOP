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

	size_t i = 0;
	for (T value : left)
	{
		CHECK(value == right[i++]);
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

		CMyArray copy{ array };

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

		CMyArray moved{ std::move(array) };

		CompareArrayAndVector(moved, { 5, 3, -99 });
		CompareArrayAndVector(array, {});
		CHECK(0 == array.Capacity());
	}

	SECTION("Moving assignment")
	{
		CMyArray<int> array{}, moved{};
		array.PushBack(5);
		array.PushBack(3);
		array.PushBack(-99);

		moved = std::move(array);

		CompareArrayAndVector(moved, { 5, 3, -99 });
		CompareArrayAndVector(array, {});
		CHECK(0 == array.Capacity());
	}
}

TEST_CASE("Increases size if reached limit", "[array][alloc]")
{
	CMyArray<int> array{};

	CHECK(0 == array.Size());
	CHECK(0 == array.Capacity());

	array.PushBack(5);

	CHECK(1 == array.Size());
	CHECK(1 == array.Capacity());

	array.PushBack(4);

	CHECK(2 == array.Size());
	CHECK(2 == array.Capacity());

	array.PushBack(111);

	CHECK(3 == array.Size());
	CHECK(4 == array.Capacity());
	CompareArrayAndVector(array, { 5, 4, 111 });
}

TEST_CASE("Can access items by index", "[array][index]")
{

	CMyArray<std::string> array{};
	array.PushBack("first");
	array.PushBack("second");
	array.PushBack("last");

	CHECK("first" == array[0]);
	CHECK("second" == array[1]);
	CHECK("last" == array[2]);
	CHECK_THROWS_AS(array[3], std::out_of_range);
}

TEST_CASE("Can be cleared", "[array][clear]")
{
	CMyArray<std::string> array{};

	array.PushBack("first");
	array.PushBack("second");
	array.PushBack("last");

	CompareArrayAndVector(array, { "first", "second", "last" });

	array.Clear();

	CompareArrayAndVector(array, {});
	CHECK(0 == array.Capacity());
}

TEST_CASE("Can be resized", "[array][clear]")
{
	CMyArray<std::string> array{};

	array.PushBack("first");
	array.PushBack("second");
	array.PushBack("last");

	CompareArrayAndVector(array, { "first", "second", "last" });
	CHECK(4 == array.Capacity());

	array.Resize(6);

	CompareArrayAndVector(array, { "first", "second", "last" });
	CHECK(6 == array.Capacity());

	array.Resize(2);
	CompareArrayAndVector(array, { "first", "second" });
	CHECK(2 == array.Capacity());
}