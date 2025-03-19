#include "../lib/PrimeNumbers.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include <set>

TEST_CASE("Find prime numbers up to upper bound", "[positive]")
{
	const std::set expected = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

	const std::set<int> actual = GeneratePrimeNumbersSet(30);

	REQUIRE(expected == actual);
}

#ifdef NDEBUG
TEST_CASE("Finds prime numbers up to upper bound less 12 seconds", "[positive][benchmark]")
{
	const auto start = std::chrono::system_clock::now();

	const std::set<int> set = GeneratePrimeNumbersSet(100'000'000);

	const auto end = std::chrono::system_clock::now();
	const std::chrono::duration<double> elapsed = end - start;
	REQUIRE(set.size() == 5761455);
	REQUIRE(elapsed.count() < 12000);
}
#endif

TEST_CASE("Prints set in output", "[positive][print]")
{
	std::ostringstream out;
	const std::set set = { 3, 5, 7, 11, 13, 17, 19, 23, 29 };

	PrintSet(out, set);

	REQUIRE(out.str() == "3\n5\n7\n11\n13\n17\n19\n23\n29\n");
}

// Negative

TEST_CASE("Cannot process unsupported data", "[negative][convert]")
{
	REQUIRE_THROWS_MATCHES(
		GeneratePrimeNumbersSet(100'000'001),
		std::invalid_argument,
		Catch::Matchers::Message("Upper bound must be between 0 and 100000000"));
	REQUIRE_THROWS_MATCHES(
		GeneratePrimeNumbersSet(-1),
		std::invalid_argument,
		Catch::Matchers::Message("Upper bound must be between 0 and 100000000"));
}