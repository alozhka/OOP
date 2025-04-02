cmake_minimum_required(VERSION 3.30)
project(calculator)

set(CMAKE_CXX_STANDARD 20)

# Tests
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(unit_tests tests/UnitTests.cpp
        source/Calculator.cpp
        source/Function.cpp
        source/Operation.cpp
        source/Variable.cpp
        source/CalculatorController.cpp)

target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)

add_executable(calculator main.cpp
        source/Calculator.cpp
        source/Variable.cpp
        source/Function.cpp
        source/Operation.cpp
        source/CalculatorController.cpp)
