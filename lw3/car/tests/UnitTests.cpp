#include "../include/CarController.h"
#include "../source/Car.cpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_compiler_capabilities.hpp>
#include <catch2/internal/catch_test_registry.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

TEST_CASE("Supports command to manipulate car", "[controller][commands]")
{
	Car car;
	std::istringstream in("EngineOn\nSetGear -1\nSetSpeed 5\nInfo\nSetGear 0\nSetSpeed 0\nEngineOff\n");
	std::ostringstream out;
	std::string expected = "Engine: on\nDirection: backward\nSpeed: 5\nGear: -1\n";
	CarController controller(car, in, out);

	while (controller.HandleCommand())
	{
	}

	REQUIRE(in.eof());
	REQUIRE(expected == out.str());
}

TEST_CASE("Car prints info", "[controller][info]")
{
	Car car;
	std::istringstream in("Info\nEngineOn\nSetGear 1\nSetSpeed 25\nInfo\n");
	std::ostringstream out;
	CarController controller(car, in, out);
	std::string expected1 = "Engine: off\nDirection: standing still\nSpeed: 0\nGear: 0\n";
	std::string expected2 = "Engine: on\nDirection: forward\nSpeed: 25\nGear: 1\n";

	controller.HandleCommand();
	REQUIRE(expected1 == out.str());

	out.str("");

	while (controller.HandleCommand())
	{
	}
	REQUIRE(expected2 == out.str());
}

TEST_CASE("Car changes speed according to gear", "[car][speed]")
{
	Car car;

	car.TurnOnEngine();
	car.SetGear(1);

	REQUIRE_THROWS_MATCHES(car.SetSpeed(31), std::runtime_error, Catch::Matchers::Message("Unsuitable current speed"));

	car.SetSpeed(30);
	car.SetGear(2);

	car.SetSpeed(45);
	car.SetGear(0);

	REQUIRE_THROWS_MATCHES(car.SetSpeed(46), std::runtime_error, Catch::Matchers::Message("Unsuitable current speed"));
}

TEST_CASE("Car changes gear according to speed", "[car][speed]")
{
	Car car;

	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(25);

	REQUIRE_THROWS_MATCHES(car.SetGear(3), std::runtime_error, Catch::Matchers::Message("Unsuitable current gear"));
}

TEST_CASE("Engine stops only in neutral gear and no speed", "[car][engine]")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(5);

	REQUIRE_THROWS_MATCHES(
		car.TurnOffEngine(),
		std::runtime_error,
		Catch::Matchers::Message("Сar must be stopped and in neutral gear"));

	car.SetSpeed(0);

	REQUIRE_THROWS_MATCHES(
		car.TurnOffEngine(),
		std::runtime_error,
		Catch::Matchers::Message("Сar must be stopped and in neutral gear"));

	car.SetGear(0);

	car.TurnOffEngine();
}

// negative

TEST_CASE("Process only valid gear and speed number", "[negative][controller][converter]")
{
	Car car;
	std::ostringstream out;
	std::istringstream in("EngineOn\nSetGear notanumber\nSetSpeed notanumber");
	std::string expected = "Invalid command argument\n";
	CarController controller(car, in, out);

	controller.HandleCommand();
	controller.HandleCommand();

	REQUIRE(expected == out.str());

	out.str("");
	controller.HandleCommand();

	REQUIRE(expected == out.str());
}

TEST_CASE("Cannot process unexpected command", "[negative][controller][converter]")
{
	Car car;
	std::ostringstream out;
	std::istringstream in("Unknowncommand\n");
	CarController controller(car, in, out);

	REQUIRE_FALSE(controller.HandleCommand());
}

TEST_CASE("Car cannot set unsupported gear and speed", "[negative][car][gear][speed]")
{
	Car car;
	car.TurnOnEngine();

	REQUIRE_THROWS_MATCHES(car.SetGear(-2), std::runtime_error, Catch::Matchers::Message("Invalid gear"));
	REQUIRE_THROWS_MATCHES(car.SetGear(6), std::runtime_error, Catch::Matchers::Message("Invalid gear"));
	REQUIRE_THROWS_MATCHES(car.SetSpeed(-10), std::runtime_error, Catch::Matchers::Message("Speed must be positive number"));
}

TEST_CASE("Cannot control car if engine is turned off", "[negative][car][engine]")
{
	Car car;

	REQUIRE_THROWS_MATCHES(car.SetGear(1), std::runtime_error, Catch::Matchers::Message("Gear is settable when engine is turned on"));
	REQUIRE_THROWS_MATCHES(car.SetSpeed(7), std::runtime_error, Catch::Matchers::Message("Speed is settable when engine is turned on"));
}

TEST_CASE("Car needs to stop to move forward if it moves backward", "[negative][car][gear]")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(8);

	REQUIRE_THROWS_MATCHES(
		car.SetGear(1),
		std::runtime_error,
		Catch::Matchers::Message("Unsuitable current gear"));

	car.SetGear(0);
	car.SetGear(-1);
	car.SetSpeed(9);
	car.SetGear(0);

	REQUIRE_THROWS_MATCHES(
		car.SetGear(1),
		std::runtime_error,
		Catch::Matchers::Message("Unsuitable current gear"));
}