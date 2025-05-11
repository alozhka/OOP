#include "CStringList.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("Inserts values in beginning or end", "[list][insert]")
{
	CStringList list;

	CHECK(list.IsEmpty());
	CHECK(0 == list.GetSize());

	list.PushBack("hello");
	list.PushBack("world");


	auto it = list.begin();

	CHECK(*it == "hello");
	++it;
	CHECK(*it == "world");
}