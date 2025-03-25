cmake_minimum_required(VERSION 3.30)
project(car)

set(CMAKE_CXX_STANDARD 20)

# Tests
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(unit_tests tests/UnitTests.cpp
        source/CarController.cpp
        include/CarController.h
)
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)

add_executable(car main.cpp
        source/Car.cpp
        source/CarController.cpp
        include/CarController.h
)
