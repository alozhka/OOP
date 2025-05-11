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

TEST_CASE("Inserts values in beginning or end", "[list][insert]")
{
	CStringList list;

	CHECK(list.IsEmpty());
	CHECK(0 == list.GetSize());

	list.PushBack("hello");
	list.PushBack("world");

	CheckList(list, { "hello", "world" });

	list.PushFront("My");

	CheckList(list, { "My", "hello", "world" });
}