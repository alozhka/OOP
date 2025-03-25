#include "../include/CarController.h"
#include "../source/Car.cpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_compiler_capabilities.hpp>
#include <catch2/internal/catch_test_registry.hpp>

TEST_CASE("Car car ride", "[positive][car]")
{
	Car car;
	std::istringstream in("Info\n");
	std::ostringstream out;
	std::string expected = "Engine: off\nDirection: standing still\nSpeed: 0\nGear: 0\n";
	CarController controller(car, in, out);

	bool success = controller.HandleCommand();

	REQUIRE(true == success);
	REQUIRE(expected == out.str());
}