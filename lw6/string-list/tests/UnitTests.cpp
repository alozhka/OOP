#include "CStringList.h"
#include "catch2/catch_test_macros.hpp"

void CheckList(const CStringList& list, const std::vector<std::string>& values)
{
	CHECK(list.GetSize() == values.size());

	size_t i = 0;
	for (std::string value : list)
	{
		CHECK(value == values[i++]);
	}
}

void CheckEquality(const CStringList& left, const CStringList& right)
{
	CHECK(left.GetSize() == right.GetSize());

	auto it = left.begin();
	for (std::string value : right)
	{
		CHECK(*it == value);
		++it;
	}
}

TEST_CASE("Inserts values", "[list][insert]")
{
	CStringList list;

	CHECK(list.IsEmpty());
	CHECK(0 == list.GetSize());

	list.PushBack("hello");
	list.PushBack("world");

	CheckList(list, { "hello", "world" });

	list.PushFront("My");

	CheckList(list, { "My", "hello", "world" });

	auto it = list.begin();
	list.Insert(it, "First");
	++it;
	++it;
	list.Insert(it, "beautiful");

	CheckList(list, { "First", "My", "hello", "beautiful", "world" });
	CHECK(!list.IsEmpty());
	CHECK(5 == list.GetSize());
}

TEST_CASE("Can clear list", "[list][clear]")
{
	CStringList list;
	list.PushBack("world");
	list.PushFront("hello");

	CHECK(!list.IsEmpty());
	CHECK(2 == list.GetSize());

	list.Clear();

	CHECK(list.IsEmpty());
	CHECK(0 == list.GetSize());
	CheckList(list, {});
}

TEST_CASE("Can be created differently", "[list][ctor][assign]")
{
	SECTION("Copying constructor")
	{
		CStringList list;
		list.PushBack("hello");
		list.PushBack("world");

		CStringList copy(list);

		CheckEquality(list, copy);
	}

	SECTION("Moving constructor")
	{
		CStringList initial;
		initial.PushBack("hello");
		initial.PushBack("world");

		CStringList moved(std::move(initial));

		CHECK(!moved.IsEmpty());
		CheckList(moved, { "hello", "world" });
		CHECK(initial.IsEmpty());
		CheckList(initial, {});
	}

	SECTION("Copying assignment")
	{
		CStringList initial;
		initial.PushBack("hello");
		initial.PushBack("world");
		CStringList copy;

		copy = initial;

		CheckEquality(copy, initial);
	}

	SECTION("Moving assignment")
	{
		CStringList initial;
		initial.PushBack("hello");
		initial.PushBack("world");
		CStringList moved;

		moved = std::move(initial);

		CHECK(!moved.IsEmpty());
		CheckList(moved, { "hello", "world" });
		CHECK(initial.IsEmpty());
		CheckList(initial, {});
	}
}